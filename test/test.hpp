#ifndef test_hpp
#define test_hpp

#define TEST(name) auto test_##name = []() {
#define ENDTEST(name) }; test_##name();

#define TEST_ASSERT(x) { bool b = (x); if (!b) std::cerr << "assertion " << #x << " failed at " << __FILE__ << ":" << __LINE__ << std::endl; if(!b) exit(1); }

#endif
