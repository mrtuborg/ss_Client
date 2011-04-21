#ifndef TEST_console_outTest
#define TEST_console_outTest

#ifdef ECUT_MAIN

#include "cppunit/extensions/HelperMacros.h"

class console_outTest : public CPPUNIT_NS::TestFixture {
public:
	void testshow_help();
	void testshow_version();
	void testshow_error();
	void testinternal_error();
	void testoptname();
	CPPUNIT_TEST_SUITE(console_outTest);
	CPPUNIT_TEST(testshow_help);
	CPPUNIT_TEST(testshow_version);
	CPPUNIT_TEST(testshow_error);
	CPPUNIT_TEST(testinternal_error);
	CPPUNIT_TEST(testoptname);
	CPPUNIT_TEST_SUITE_END();
};

#endif /* ECUT_MAIN */

#endif /*CONSOLE_OUTTEST*/
