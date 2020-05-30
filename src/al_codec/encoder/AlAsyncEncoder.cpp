/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "include/AlAsyncEncoder.h"
#include "include/AlFFEncoder.h"

#define TAG "AlAsyncEncoder"

AlAsyncEncoder::AlAsyncEncoder(const AlAbsEncoder::Desc &desc) : AlAbsVideoEncoder(desc) {
    released = false;
    hwFrameAllocator = new HwFrameAllocator();
    encoder = new AlFFEncoder(desc);
    pipeline = AlEventPipeline::create(TAG);
}

AlAsyncEncoder::~AlAsyncEncoder() {
    if (pipeline) {
        delete pipeline;
        pipeline = nullptr;
    }
    if (encoder) {
        delete encoder;
        encoder = nullptr;
    }
    AlLogI(TAG, "size %d, %d, %d", aQueue.size(), vQueue.size(), tQueue.size());
    while (!aQueue.empty()) {
        aQueue.pop();
    }
    while (!vQueue.empty()) {
        vQueue.pop();
    }
    if (hwFrameAllocator) {
        delete hwFrameAllocator;
        hwFrameAllocator = nullptr;
    }
}

void AlAsyncEncoder::setBitrate(int32_t rate) {
    encoder->setBitrate(rate);
}

void AlAsyncEncoder::setProfile(std::string profile) {
    encoder->setProfile(profile);
}

void AlAsyncEncoder::setPreset(std::string preset) {
    encoder->setPreset(preset);
}

bool AlAsyncEncoder::prepare(string path, int width, int height, HwSampleFormat audioFormat) {
    if (encoder) {
        looping = encoder->prepare(path, width, height, audioFormat);
        loop();
        return looping;
    }
    return false;
}

HwResult AlAsyncEncoder::write(HwAbsMediaFrame *frame) {
    if (released) {
        return Hw::FAILED;
    }
    if (vQueue.size() >= MAX_V_FRAME_CACHE && frame->isVideo()) {
        AlLogE(TAG, "Lack of cache, vQueue(%d), aQueue(%d), Skip Video Frame: pts=%"
                PRId64, vQueue.size(), aQueue.size(), frame->getPts());
        return Hw::FAILED;
    }
    HwAbsMediaFrame *temp = hwFrameAllocator->ref(frame);
    if (temp) {
        simpleLock.lock();
        if (temp->isAudio()) {
            aQueue.push(temp);
        } else {
            vQueue.push(temp);
        }
        tQueue.push(temp->isAudio());
        simpleLock.unlock();
        writeBlock.notify();
        return Hw::SUCCESS;
    }
    return Hw::FAILED;
}

void AlAsyncEncoder::write() {
    while (tQueue.empty()) {
        writeBlock.wait();
        if (!looping) {
            return;
        }
    }
    simpleLock.lock();
    if (looping && encoder && !aQueue.empty() && !vQueue.empty() && !tQueue.empty()) {
        HwAbsMediaFrame *frame = nullptr;
        if (tQueue.front()) {
            frame = aQueue.front();
            aQueue.pop();
        } else {
            frame = vQueue.front();
            vQueue.pop();
        }
        tQueue.pop();
        if (frame) {
            encoder->write(frame);
            frame->recycle();
        }
    }
    simpleLock.unlock();
}

void AlAsyncEncoder::loop() {
    simpleLock.lock();
    if (!looping) {
        simpleLock.unlock();
        return;
    }
    simpleLock.unlock();
    if (!pipeline)
        return;
    pipeline->queueEvent([this]() {
        this->write();
        this->loop();
    });
}

bool AlAsyncEncoder::stop() {
    simpleLock.lock();
    looping = false;
    bool ret = false;
    if (encoder) {
        ret = encoder->stop();
    }
    simpleLock.unlock();
    writeBlock.notify();
    return ret;
}

void AlAsyncEncoder::release() {
    released = true;
    if (encoder) {
        return encoder->release();
    }
}
