#include <iostream>
#include <rice/Data_Type.hpp>
#include <rice/Constructor.hpp>

using namespace Rice;

class Hello {
    public:
        Hello() {};
        void say() { std::cout << "Hello Ruby Extension!" << std::endl; };
};

extern "C" {
    void Init_hello() {
        Data_Type<Hello> rb_cHello = define_class<Hello>("Hello")
            .define_constructor(Constructor<Hello>())
            .define_method("say", &Hello::say);
    }
}