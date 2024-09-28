#include <gtest/gtest.h>
#include <world.h>

#include <memory>

#include "ecs_pointer.h"

namespace ignosi::ecs::test {
struct Component1 {
  float X{0.0};
  float Y{0.0};
  float Z{0.0};

  friend bool operator==(const Component1& rhs,
                         const Component1& lhs) = default;
};

class System1 : public System {
  bool m_HasProcessed{false};

 public:
  ~System1() override = default;
  void Process(double delta) override { m_HasProcessed = true; }
  std::uint32_t Priority() const override { return 0U; }

  bool IsProcessed() const { return m_HasProcessed; }
};

class WorldFixture : public testing::Test {
 protected:
  std::unique_ptr<World> m_pWorld;

 public:
  WorldFixture() : m_pWorld(std::make_unique<World>(256)) {}
  ~WorldFixture() { m_pWorld.reset(); }
};

TEST_F(WorldFixture, ValidateInitialization) {}

TEST_F(WorldFixture, ValidateCreateEntity) {
  ECSPointer<Entity> entity = m_pWorld->CreateEntity();
  ASSERT_EQ(entity->RegisteredComponents().to_ulong(), 0);
}

TEST_F(WorldFixture, ValidateCreateMultipleEntities) {
  ECSPointer<Entity> entity1 = m_pWorld->CreateEntity();
  ECSPointer<Entity> entity2 = m_pWorld->CreateEntity();
  ASSERT_NE(entity1->ID(), entity2->ID());
}

TEST_F(WorldFixture, ValidateRegisterComponent) {
  m_pWorld->RegisterComponent<Component1>();
  ECSPointer<Entity> entity = m_pWorld->CreateEntity();

  ECSPointer<Component<Component1>> pComponent =
      m_pWorld->CreateComponent<Component1>(*entity);
  ASSERT_EQ(pComponent->Data, Component1{});
}

TEST_F(WorldFixture, ValidateRegisterSystem) {
  ASSERT_NO_THROW(auto system =
                      m_pWorld->RegisterSystem(std::make_unique<System1>()));
}

TEST_F(WorldFixture, ValidateRegisterQuery) {
  ASSERT_NO_THROW(auto query = m_pWorld->RegisterQuery(std::make_unique<Query>(
                      [](const Entity& entity) { return true; })));
}

TEST_F(WorldFixture, ValidateProcessSystem) {
  ECSPointer<System1> system =
      m_pWorld->RegisterSystem(std::make_unique<System1>());
  m_pWorld->Process(0.1);
  ASSERT_TRUE(system->IsProcessed());
}

}  // namespace ignosi::ecs::test
