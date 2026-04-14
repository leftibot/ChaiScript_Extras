#ifndef CHAISCRIPT_EXTRAS_RANDOM_HPP_
#define CHAISCRIPT_EXTRAS_RANDOM_HPP_

#include <memory>
#include <random>

#include <chaiscript/chaiscript.hpp>

namespace chaiscript {
  namespace extras {
    namespace random {
      ModulePtr bootstrap(ModulePtr m = std::make_shared<Module>())
      {
        auto engine = std::make_shared<std::mt19937>(std::random_device{}());

        m->add(chaiscript::fun([engine]() -> int {
          std::uniform_int_distribution<int> dist(0, RAND_MAX);
          return dist(*engine);
        }), "rand");

        m->add(chaiscript::fun([engine](int max) -> int {
          std::uniform_int_distribution<int> dist(0, max);
          return dist(*engine);
        }), "rand");

        m->add(chaiscript::fun([engine](int min, int max) -> int {
          std::uniform_int_distribution<int> dist(min, max);
          return dist(*engine);
        }), "rand");

        m->add(chaiscript::fun([engine](unsigned int seed) {
          engine->seed(seed);
        }), "srand");

        return m;
      }
    }
  }
}

#endif /* CHAISCRIPT_EXTRAS_RANDOM_HPP_ */
