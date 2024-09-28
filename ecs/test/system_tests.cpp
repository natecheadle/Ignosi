
#include <fmt/format.h>
#include <gtest/gtest.h>
#include <world.h>

#include <memory>

#include "ecs_pointer.h"
#include "entity.h"
#include "query.h"

namespace ignosi::ecs::test {
struct System2Component {
  float X{0.0};
  float Y{0.0};
  float Z{0.0};

  float DX{0.0};
  float DY{0.0};
  float DZ{0.0};

  friend bool operator==(const System2Component& rhs,
                         const System2Component& lhs) = default;

  friend std::ostream& operator<<(std::ostream& os,
                                  const System2Component& obj) {
    os << ".X = " << obj.X << " .Y = " << obj.Y << " .Z = " << obj.Z
       << " .DX = " << obj.DX << " .DY = " << obj.DY << " .DZ = " << obj.DZ;
    return os;
  }
};

class System2 : public System {
  ECSPointer<Query> m_pComponentQuery;

 public:
  System2(ECSPointer<Query> pQuery) : m_pComponentQuery(std::move(pQuery)) {}
  ~System2() override = default;
  void Process(double delta) override {
    for (const Entity* entity : m_pComponentQuery->Result()) {
      System2Component* pComponent = entity->GetComponent<System2Component>();
      pComponent->X += pComponent->DX * delta;
      pComponent->Y += pComponent->DY * delta;
      pComponent->Z += pComponent->DZ * delta;
    }
  }
  std::uint32_t Priority() const override { return 0U; }
};

class SystemFixture : public testing::Test {
 protected:
  std::unique_ptr<World> m_pWorld;
  ECSPointer<System2> m_pSystem;

 public:
  SystemFixture() : m_pWorld(std::make_unique<World>(256)) {
    m_pWorld->RegisterComponent<System2Component>();
    auto pSystemQuery = m_pWorld->RegisterQuery(
        std::make_unique<Query>([](const Entity& entity) {
          return entity.RegisteredComponents()
              [Component<System2Component>::StaticTypeIDValue()];
        }));
    m_pSystem = m_pWorld->RegisterSystem<System2>(
        std::make_unique<System2>(std::move(pSystemQuery)));
  }

  ~SystemFixture() {
    m_pSystem.reset();
    m_pWorld.reset();
  }
};

TEST_F(SystemFixture, ValidateInitialization) {}

TEST_F(SystemFixture, ValidateSystemUpdate) {
  ECSPointer<Entity> entity = m_pWorld->CreateEntity();

  ECSPointer<Component<System2Component>> pComponent =
      m_pWorld->CreateComponent<System2Component>(
          *entity,
          {.X = 0.0, .Y = 1.0, .Z = 2.0, .DX = 2.0, .DY = 1.0, .DZ = 0.0});
  m_pWorld->Process(1.0);

  ASSERT_EQ(
      pComponent->Data,
      System2Component(
          {.X = 2.0, .Y = 2.0, .Z = 2.0, .DX = 2.0, .DY = 1.0, .DZ = 0.0}));
}

}  // namespace ignosi::ecs::test
