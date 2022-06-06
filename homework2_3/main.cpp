#include <thread_pool.h>
#include <thread>
#include <ctime>
#include <cstdlib>

int main()
{
    using namespace std;
    srand(time(NULL));
    mutex cout_guard;
    cout << this_thread::get_id() << endl;
    thread_pool tp;
    for(auto i = 1; i <= 10; ++i){
        tp.do_work([&, i = 1]()
    }      
    unique_lock guard(cout_guard);
    cout << i << endl;   
    this_thread::sleep_for(chrono::milliseconds(rand()%1000));
} 
