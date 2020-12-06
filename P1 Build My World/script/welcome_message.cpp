#include <gazebo/gazebo.hh>

namespace gazebo {
  class WorldPluginMyRobot : public WorldPlugin {
    public:
      /** Constructor */
      WorldPluginMyRobot() : WorldPlugin() {
        printf("Welcome to FeLIX's World!\n");
      }
      
      /** Load world model */
      void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) { }
  };
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginMyRobot)
}
