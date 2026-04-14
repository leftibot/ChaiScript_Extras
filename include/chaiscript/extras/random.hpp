#ifndef CHAISCRIPT_EXTRAS_RANDOM_HPP_
#define CHAISCRIPT_EXTRAS_RANDOM_HPP_

#include <memory>
#include <random>

#include <chaiscript/chaiscript.hpp>

namespace chaiscript {
  namespace extras {
    namespace random {
      class Random_Engine {
      public:
        Random_Engine()
          : m_engine(std::random_device{}())
        {
        }

        explicit Random_Engine(unsigned int t_seed)
          : m_engine(t_seed)
        {
        }

        Random_Engine(const Random_Engine &) = default;
        Random_Engine &operator=(const Random_Engine &) = default;

        void seed(unsigned int t_seed) {
          m_engine.seed(t_seed);
        }

        int random_int(int t_min, int t_max) {
          std::uniform_int_distribution<int> dist(t_min, t_max);
          return dist(m_engine);
        }

        double random_float(double t_min, double t_max) {
          std::uniform_real_distribution<double> dist(t_min, t_max);
          return dist(m_engine);
        }

      private:
        std::mt19937 m_engine;
      };

      ModulePtr bootstrap(ModulePtr m = std::make_shared<Module>())
      {
        m->add(user_type<Random_Engine>(), "Random_Engine");
        m->add(constructor<Random_Engine ()>(), "Random_Engine");
        m->add(constructor<Random_Engine (unsigned int)>(), "Random_Engine");
        m->add(constructor<Random_Engine (const Random_Engine &)>(), "Random_Engine");

        m->add(fun(&Random_Engine::seed), "seed");
        m->add(fun(&Random_Engine::random_int), "random_int");
        m->add(fun(&Random_Engine::random_float), "random_float");

        m->add(fun([](Random_Engine &t_lhs, const Random_Engine &t_rhs) -> Random_Engine & {
          t_lhs = t_rhs;
          return t_lhs;
        }), "=");

        return m;
      }
    }
  }
}

#endif /* CHAISCRIPT_EXTRAS_RANDOM_HPP_ */
