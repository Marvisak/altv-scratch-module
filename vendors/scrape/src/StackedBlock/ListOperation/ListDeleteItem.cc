#include <memory>
#include "StackedBlock/StackedBlock.h"
#include "NestedBlock/NestedBlock.h"
#include "StackedBlock/ListOperation/ListDeleteItem.h"
#include "NestedBlock/RoundBlock/List/List.h"

ListDeleteItem::ListDeleteItem(std::shared_ptr<List> l,const std::shared_ptr<NestedBlock> i)
    : list(l),index(i){}
void ListDeleteItem::exec() const
{
    int deleteIndex=index->getDouble()-1;
    if(deleteIndex>=0&&deleteIndex<list->length())
    {
        list->remove(deleteIndex);
    }
}
