#pragma once
#include <string>


// ========== Bean ==========
class Bean{
  std::string name;
  
public:
  Bean(std::string const& name);

  // getter function for name of a bean
  // return: strd::string - name
  std::string const& getName() const;

};


// ======= Ingredients =======
class Ingredient{
  Bean bean;
  long amount;
  
public:
  // constructor
  Ingredient(Bean const& bean, long amount);
  // copy assignment
  Ingredient(Ingredient const& other);
  // pointer to next ingredient in the linked list
  Ingredient* next = nullptr;

  // getter function for member - bean
  // return: Bean - bean
  Bean const& getBean() const;

  // getter funciton for amount of bean
  // return: long - amount
  long getAmount() const;

  // setter function for amount of bean
  // argument: long - new amount for bean
  void setAmount(long newAmount);
};

// ====== Event Values ======

class EventValue{
  long value;
  
public:
  // constructor
  EventValue(long value);
  // getter fucntion for value of event
  // return: long - value
  long getValue() const;
  // setter function for value of event
  // argument: long - new value for event
  void setValue(long newValue);

};

// ========= Events =========
class Event{
  std::string type;
  long timestamp;
  EventValue* eventValue = nullptr;
  
public:
  // constructor, EventValue is OPTIONAL
  Event(std::string const& type, long timestamp, EventValue* const& eventValue);
  Event(std::string const& type, long timestamp);
  // copy assignment of class Event
  Event(Event const& other);
  // overloading = operator for copy assignment
  Event& operator=(Event const& other);
  // destructor
  ~Event();

  // pointer to next event in the linked lis
  Event* next = nullptr;

  // getter function for timestamp of an event
  // return: long - timestamp
  long getTimestamp() const;

  // getter function for event type
  // return: std::string - type
  std::string const& getType() const;

  // helper funciton, check if an event has an event value or not
  bool hasValue() const;

  // getter function for value of an event
  // return: pointer of EventValue
  EventValue* getValue() const;
};


// ========= Roast ==========
class Roast{
  long id;
  long timestamp;
  Ingredient* ingredient = nullptr;
  Event* event = nullptr;
  int numIngredients = 0;// number of ingredients
  int numEvents = 0;// number of events
  
public:

  // constructor
  Roast(long id, long timestamp);
  Roast(long timestamp); // when only timestamp is provided

  // copy assignment
  Roast(Roast const& other);

  // overloading = operator for copy assignment
  Roast& operator=(Roast const& other);

  // dectructor
  ~Roast();


  // getter function for roast id
  // return: long - id of the roast
  long getId() const;

  // getter function for roast timestamp
  // return: long timestamp of the roast
  long getTimestamp() const;

  // getter function for ingredient in a roast
  // argument: index of ingredient
  // return: ingredient object
  Ingredient& getIngredient(int i);
  Ingredient const& getIngredient(int i) const;

  // getter funciton for number of ingredients
  // return: number of ingredients
  int getIngredientsCount() const;

  // add agredient to the linked list
  // argument: new ingreident object
  void addIngredient(Ingredient const& newIngredient);

  // getter funciton for event in roast
  // argument: index for the event
  // return: event object with index i
  Event const& getEvent(int i) const;

  // getter function fot number of events in a roast
  int getEventCount() const;

  // get an event by its timestamp
  // argument: event timestamp
  // return: event object
  Event const& getEventByTimestamp(long ts) const;

  // add a new event to the linked list
  // argument: new event object
  void addEvent(Event const& newEvent);

  // remove an event by its timestamp
  // argument: timestamp of the event
  void removeEventByTimestamp(long ts);

  // remove an ingredient by bean name
  // argument: std::string - bean name
  void removeIngredientByBeanName(std::string const& beanName);
};


