// SPDX-License-Identifier: GPL-2.0
#include "testqPrefFacebook.h"

#include "core/settings/qPref.h"
#include "core/pref.h"
#include "core/qthelper.h"

#include <QTest>

void TestQPrefFacebook::initTestCase()
{
	QCoreApplication::setOrganizationName("Subsurface");
	QCoreApplication::setOrganizationDomain("subsurface.hohndel.org");
	QCoreApplication::setApplicationName("SubsurfaceTestQPrefFacebook");
}

void TestQPrefFacebook::test_struct_get()
{
	// Test struct pref -> get func.

	auto tst = qPrefFacebook::instance();

	prefs.facebook.access_token = copy_qstring("t1 token");
	prefs.facebook.album_id = copy_qstring("t1 album");
	prefs.facebook.user_id = copy_qstring("t1 user");

	QCOMPARE(tst->access_token(), QString(prefs.facebook.access_token));
	QCOMPARE(tst->album_id(), QString(prefs.facebook.album_id));
	QCOMPARE(tst->user_id(), QString(prefs.facebook.user_id));
}

void TestQPrefFacebook::test_set_struct()
{
	// Test set func -> struct pref

	auto tst = qPrefFacebook::instance();

	tst->set_access_token("t2 token");
	tst->set_album_id("t2 album");
	tst->set_user_id("t2 user");

	QCOMPARE(QString(prefs.facebook.access_token), QString("t2 token"));
	QCOMPARE(QString(prefs.facebook.album_id), QString("t2 album"));
	QCOMPARE(QString(prefs.facebook.user_id), QString("t2 user"));
}

void TestQPrefFacebook::test_multiple()
{
	// test multiple instances have the same information

	prefs.facebook.access_token = copy_qstring("test 1");
	auto tst_direct = new qPrefFacebook;

	prefs.facebook.access_token = copy_qstring("test 2");
	auto tst = qPrefFacebook::instance();

	QCOMPARE(tst->access_token(), tst_direct->access_token());
}

#define TEST(METHOD, VALUE) \
QCOMPARE(METHOD, VALUE); \
fb->sync(); \
fb->load(); \
QCOMPARE(METHOD, VALUE);

void TestQPrefFacebook::test_oldPreferences()
{
	auto fb = qPrefFacebook::instance();
	fb->set_access_token("rand-access-token");
	fb->set_user_id("tomaz-user-id");
	fb->set_album_id("album-id");

	TEST(fb->access_token(),QStringLiteral("rand-access-token"));
	TEST(fb->user_id(),     QStringLiteral("tomaz-user-id"));
	TEST(fb->album_id(),    QStringLiteral("album-id"));

	fb->set_access_token("rand-access-token-2");
	fb->set_user_id("tomaz-user-id-2");
	fb->set_album_id("album-id-2");

	TEST(fb->access_token(),QStringLiteral("rand-access-token-2"));
	TEST(fb->user_id(),     QStringLiteral("tomaz-user-id-2"));
	TEST(fb->album_id(),    QStringLiteral("album-id-2"));
}

QTEST_MAIN(TestQPrefFacebook)
