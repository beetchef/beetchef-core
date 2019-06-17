#include <string>
using namespace std;

class Engine {
        public:
                Engine();
                int startEngine(); 
                bool isAlive();
        private:
                bool _alive;
                string getEngineStatus();
                
};