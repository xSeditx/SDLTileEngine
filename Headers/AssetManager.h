#pragma once
#include"Window.h"


template<typename T>
struct AssetManager
{
      T *GetAsset(const char *name)
        {
            for_loop(Index, Count)
            {
				if(strncmp(List[Index]->Name, name, sizeof(name)) == 0)
                //if(List[Index]->Name == name)
                {
                    return List[Index];
                }
            }
           Print("Asset " << name << " Not Registered: Please check the description of ( " << name << " ) ");
           system("Pause");
           exit(_ERROR_);
        }
      T *GetAsset(int id)
        {
            return List[id];
        }

        int  Add(T *object)
        {
            ID = Count++; 
            List.push_back(object);
            return ID;
        }
        void Delete(char *name)
        {
            Delete(GetAsset(name)->ID);
        }
        void Delete(int id)
        {
            delete(List[id]);
            Remove(id);
            //List.erase(List.begin() + id);
            //for(int Itr = id; Itr < List.size(); Itr++)
            //{
            //    List[Itr]->ID--;
            //}
        }
        void Remove(int id)
        {
            List.erase(List.begin() + (id));
            for(int Itr = id; Itr < List.size(); Itr++)
            {
                List[Itr]->ID--;
            }
        }
        void FreeAll()
        {
           for_loop(Index, List.size())
           {
               delete(List[Index]);
           }
        }
        bool IsExistant(char *name)
        {
            for(auto &L: List)
            {
                if(L.Name == name) return true;
            }
          return false;
        }

private:
        std::vector<T *> List;
        int ID;
        int Count;
};
