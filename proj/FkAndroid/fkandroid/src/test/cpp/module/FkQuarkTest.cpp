/*
* Copyright (c) 2018-present, aliminabc@gmail.com.
*
* This source code is licensed under the MIT license found in the
* LICENSE file in the root directory of this source tree.
*/

#include "gtest/gtest.h"
#include "FkIncreaseQuark.h"
#include "FkSession.h"
#include "FkSessionExecutor.h"
#include "FkOnCreatePrt.h"
#include "FkOnDestroyPrt.h"
#include "FkOnStartPrt.h"
#include "FkOnStopPrt.h"
#include "FkCalculatePrt.h"

TEST(FkQuarkTest, Create) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with(std::make_shared<FkOnCreatePrt>());
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->open(), FK_OK);
    FkSessionExecutor executor;
    EXPECT_EQ(executor.send(session, std::make_shared<FkOnCreatePrt>()), FK_OK);
    EXPECT_EQ(session->close(), FK_OK);
}

TEST(FkQuarkTest, CreateError) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with(std::make_shared<FkOnCreatePrt>());
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->open(), FK_OK);
    FkSessionExecutor executor;
    EXPECT_EQ(executor.send(session, std::make_shared<FkOnCreatePrt>()), FK_OK);
    EXPECT_NE(executor.send(session, std::make_shared<FkOnCreatePrt>()), FK_OK);
    EXPECT_EQ(session->close(), FK_OK);
}

TEST(FkQuarkTest, Start) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with(std::make_shared<FkOnCreatePrt>());
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->open(), FK_OK);
    FkSessionExecutor executor;
    EXPECT_EQ(executor.send(session, std::make_shared<FkOnCreatePrt>()), FK_OK);

    auto onStartSes = FkSession::with(std::make_shared<FkOnStartPrt>());
    EXPECT_EQ(onStartSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStartSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStartSes, std::make_shared<FkOnStartPrt>()), FK_OK);

    EXPECT_EQ(onStartSes->close(), FK_OK);
    EXPECT_EQ(session->close(), FK_OK);
}

TEST(FkQuarkTest, StartError) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with(std::make_shared<FkOnCreatePrt>());
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->open(), FK_OK);
    FkSessionExecutor executor;
    EXPECT_EQ(executor.send(session, std::make_shared<FkOnCreatePrt>()), FK_OK);

    auto onStartSes = FkSession::with(std::make_shared<FkOnStartPrt>());
    EXPECT_EQ(onStartSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStartSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStartSes, std::make_shared<FkOnStartPrt>()), FK_OK);
    EXPECT_NE(executor.send(onStartSes, std::make_shared<FkOnStartPrt>()), FK_OK);

    EXPECT_EQ(onStartSes->close(), FK_OK);
    EXPECT_EQ(session->close(), FK_OK);
}

TEST(FkQuarkTest, Stop) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with(std::make_shared<FkOnCreatePrt>());
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->open(), FK_OK);
    FkSessionExecutor executor;
    EXPECT_EQ(executor.send(session, std::make_shared<FkOnCreatePrt>()), FK_OK);

    auto onStartSes = FkSession::with(std::make_shared<FkOnStartPrt>());
    EXPECT_EQ(onStartSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStartSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStartSes, std::make_shared<FkOnStartPrt>()), FK_OK);

    auto onStopSes = FkSession::with(std::make_shared<FkOnStopPrt>());
    EXPECT_EQ(onStopSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStopSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStopSes, std::make_shared<FkOnStopPrt>()), FK_OK);

    EXPECT_EQ(onStartSes->close(), FK_OK);
    EXPECT_EQ(onStopSes->close(), FK_OK);
    EXPECT_EQ(session->close(), FK_OK);
}

TEST(FkQuarkTest, StopError) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with(std::make_shared<FkOnCreatePrt>());
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->open(), FK_OK);
    FkSessionExecutor executor;
    EXPECT_EQ(executor.send(session, std::make_shared<FkOnCreatePrt>()), FK_OK);

    auto onStartSes = FkSession::with(std::make_shared<FkOnStartPrt>());
    EXPECT_EQ(onStartSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStartSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStartSes, std::make_shared<FkOnStartPrt>()), FK_OK);

    auto onStopSes = FkSession::with(std::make_shared<FkOnStopPrt>());
    EXPECT_EQ(onStopSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStopSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStopSes, std::make_shared<FkOnStopPrt>()), FK_OK);
    EXPECT_NE(executor.send(onStopSes, std::make_shared<FkOnStopPrt>()), FK_OK);

    EXPECT_EQ(onStartSes->close(), FK_OK);
    EXPECT_EQ(onStopSes->close(), FK_OK);
    EXPECT_EQ(session->close(), FK_OK);
}

TEST(FkQuarkTest, Destroy) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with(std::make_shared<FkOnCreatePrt>());
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->open(), FK_OK);
    FkSessionExecutor executor;
    EXPECT_EQ(executor.send(session, std::make_shared<FkOnCreatePrt>()), FK_OK);

    auto onStartSes = FkSession::with(std::make_shared<FkOnStartPrt>());
    EXPECT_EQ(onStartSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStartSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStartSes, std::make_shared<FkOnStartPrt>()), FK_OK);

    auto onStopSes = FkSession::with(std::make_shared<FkOnStopPrt>());
    EXPECT_EQ(onStopSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStopSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStopSes, std::make_shared<FkOnStopPrt>()), FK_OK);

    auto onDestroySes = FkSession::with(std::make_shared<FkOnDestroyPrt>());
    EXPECT_EQ(onDestroySes->connectTo(quark), FK_OK);
    EXPECT_EQ(onDestroySes->open(), FK_OK);
    EXPECT_EQ(executor.send(onDestroySes, std::make_shared<FkOnDestroyPrt>()), FK_OK);

    EXPECT_EQ(onDestroySes->close(), FK_OK);
    EXPECT_EQ(onStartSes->close(), FK_OK);
    EXPECT_EQ(onStopSes->close(), FK_OK);
    EXPECT_EQ(session->close(), FK_OK);
}

TEST(FkQuarkTest, DestroyError) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with(std::make_shared<FkOnCreatePrt>());
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->open(), FK_OK);
    FkSessionExecutor executor;
    EXPECT_EQ(executor.send(session, std::make_shared<FkOnCreatePrt>()), FK_OK);

    auto onStartSes = FkSession::with(std::make_shared<FkOnStartPrt>());
    EXPECT_EQ(onStartSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStartSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStartSes, std::make_shared<FkOnStartPrt>()), FK_OK);

    auto onStopSes = FkSession::with(std::make_shared<FkOnStopPrt>());
    EXPECT_EQ(onStopSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStopSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStopSes, std::make_shared<FkOnStopPrt>()), FK_OK);

    auto onDestroySes = FkSession::with(std::make_shared<FkOnDestroyPrt>());
    EXPECT_EQ(onDestroySes->connectTo(quark), FK_OK);
    EXPECT_EQ(onDestroySes->open(), FK_OK);
    EXPECT_EQ(executor.send(onDestroySes, std::make_shared<FkOnDestroyPrt>()), FK_OK);
    EXPECT_NE(executor.send(onDestroySes, std::make_shared<FkOnDestroyPrt>()), FK_OK);

    EXPECT_EQ(onDestroySes->close(), FK_OK);
    EXPECT_EQ(onStartSes->close(), FK_OK);
    EXPECT_EQ(onStopSes->close(), FK_OK);
    EXPECT_EQ(session->close(), FK_OK);
}

TEST(FkQuarkTest, Increase) {
    auto quark = std::make_shared<FkIncreaseQuark>();
    auto session = FkSession::with(std::make_shared<FkOnCreatePrt>());
    EXPECT_EQ(session->connectTo(quark), FK_OK);
    EXPECT_EQ(session->open(), FK_OK);
    FkSessionExecutor executor;
    EXPECT_EQ(executor.send(session, std::make_shared<FkOnCreatePrt>()), FK_OK);

    auto onStartSes = FkSession::with(std::make_shared<FkOnStartPrt>());
    EXPECT_EQ(onStartSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStartSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStartSes, std::make_shared<FkOnStartPrt>()), FK_OK);

    auto calSes = FkSession::with(std::make_shared<FkCalculatePrt>());
    EXPECT_EQ(calSes->connectTo(quark), FK_OK);
    EXPECT_EQ(calSes->open(), FK_OK);
    auto prot = std::make_shared<FkCalculatePrt>();
    prot->number = 1.0f;
    EXPECT_EQ(executor.send(calSes, prot), FK_OK);
    EXPECT_EQ(calSes->close(), FK_OK);
    EXPECT_EQ(prot->number, 4.0f);

    auto onStopSes = FkSession::with(std::make_shared<FkOnStopPrt>());
    EXPECT_EQ(onStopSes->connectTo(quark), FK_OK);
    EXPECT_EQ(onStopSes->open(), FK_OK);
    EXPECT_EQ(executor.send(onStopSes, std::make_shared<FkOnStopPrt>()), FK_OK);

    auto onDestroySes = FkSession::with(std::make_shared<FkOnDestroyPrt>());
    EXPECT_EQ(onDestroySes->connectTo(quark), FK_OK);
    EXPECT_EQ(onDestroySes->open(), FK_OK);
    EXPECT_EQ(executor.send(onDestroySes, std::make_shared<FkOnDestroyPrt>()), FK_OK);

    EXPECT_EQ(onDestroySes->close(), FK_OK);
    EXPECT_EQ(onStartSes->close(), FK_OK);
    EXPECT_EQ(onStopSes->close(), FK_OK);
    EXPECT_EQ(session->close(), FK_OK);
}