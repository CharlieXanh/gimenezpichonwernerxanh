// Generated by dia2code
#ifndef ECHANGE__H
#define ECHANGE__H

#include "Item.h"

#define NB_ITEM 10

// Etat
/// class Echange - 
class Echange : public Etat {
  // Associations
  // Attributes
private:
  std::vector<Item> item(NB_ITEM);
  // Operations
public:
  Echange();
  ~Echange ();
  bool acheter(Item item);
  std::vector<item> getItems();
  // Setters and Getters
};

#endif