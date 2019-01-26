#ifndef test_hpp
#define test_hpp

#define TEST(name) auto test_##name = []() {
#define ENDTEST(name) }; test_##name();

#endif
