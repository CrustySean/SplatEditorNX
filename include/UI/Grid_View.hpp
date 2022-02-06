#pragma once

#include <borealis.hpp>

using namespace brls;

class GridView : public Box {
public:
    GridView();
    GridView(int columns);
    
    void addView(View* view) override;
    virtual void clearViews(bool free = true) override;
    View* getParentNavigationDecision(View* from, View* newFocus, FocusDirection direction) override;
    std::vector<View*>& getChildren();
    int getItemIndex(View* view);
    int getRows();
    int getItemsInRow(int row);

private:
    int columns = 1;
    Box* lastContainer = nullptr;
    View* lastView = nullptr;
    std::vector<View*> children;
};
