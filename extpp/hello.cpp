#include <iostream>
#include <ruby.hpp>

RB_BEGIN_DECLS

void Init_hello() {
    rb::Class klass("Hello");

    klass.define_method("initialize", [](VALUE rb_self, int argc, VALUE *argv) {
        return Qnil;
    });

    klass.define_method("say", [](VALUE rb_self) {
        std::cout << "Hello Ruby Extension!" << std::endl;
        return Qnil;
    });
}

RB_END_DECLS