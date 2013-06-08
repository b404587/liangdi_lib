#ifndef LD_OBJ_MGR_H_
#define LD_OBJ_MGR_H_

#include"ld.h"

class Ld_Obj:public ACE_Cleanup
{
public:
    Ld_Obj()
    {
        ACE_Object_Manager::at_exit(this);
    }
    virtual ~Ld_Obj()
    {
        cout << "~Ld_Obj";
    }
};


#endif
