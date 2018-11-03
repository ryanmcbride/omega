#include "glob.h"

Object *Object::create(std::string name)
{
    auto o = new Object;
    if (name.length() != 0)
        *o = *getObjectByName(name);
    return o;
}

int Object::getIdByName(std::string name)
{
    auto o = getObjectByName(name);
    if (o != nullptr)
    {
        return o->id;
    }
    return -1;
}
Object *Object::getObjectByName(std::string name)
{
    for (int i = 0; i < TOTALITEMS; i++)
    {
        if (name == Objects[i].truename)
        {
            return &Objects[i];
        }
    }
    return &Objects[0];
}
Object *Object::makeCash(int level)
{
    auto o = create("money");
    o->basevalue = random_range(level * level + 10) + 1; /* aux is AU value */
    o->objstr = cashstr();
    o->cursestr = o->truename = o->objstr;
    return o;
}

bool Object::operator==(std::string name)
{
    return name == std::string(truename);
}
Object *Object::makeWeapon(int id,Object* o)
{
    auto new_obj = o;
    if (new_obj == nullptr)
        new_obj = create();
    if (id == -1)
        id = random_range(NUMWEAPONS);
    *new_obj = Objects[WEAPONID + id];
    if ((id == 28) || (id == 29)) /* bolt or arrow */
        new_obj->number = random_range(20) + 1;
    if (new_obj->blessing == 0)
        new_obj->blessing = itemblessing();
    if (new_obj->plus == 0)
    {
        new_obj->plus = itemplus();
        if (new_obj->blessing < 0)
            new_obj->plus = -1 - abs(new_obj->plus);
        else if (new_obj->blessing > 0)
            new_obj->plus = 1 + abs(new_obj->plus);
    }
    return new_obj;
}