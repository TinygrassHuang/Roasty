#include <iostream>
#include <string>
#include "RoastyModel.hpp"


// ========== Bean ==========

// constructor for class Bean
Bean::Bean(std::string const& name):name(name){}

// getter function for name
// return: std::string - name
std::string const& Bean::getName() const{
  return name;
}

// ======= Ingredients =======

// constructor for class Ingredient
Ingredient::Ingredient(Bean const& bean, long amount):bean(bean),amount(amount){}

// copy assignment
Ingredient::Ingredient(Ingredient const& other):bean(other.bean),amount(other.amount),next(other.next){}

// getter funciton for memeber - bean
// return: Bean - bean
Bean const& Ingredient::getBean() const{
  return bean;
}

// getter function for amount of bean
// return: long - amount
long Ingredient::getAmount() const{
  return amount;
};

// assignment function for amount
// argument: long - new amount for bean
void Ingredient::setAmount(long newAmount){
  amount = newAmount;
}

// ====== Event Values ======

// constructor for class EventValue
// argument: long - value for event
EventValue::EventValue(long value):value(value){}


// getter function for value of event
// return: long - value
long EventValue::getValue() const{
  return value;
}

// assignment function for value of event
// argument: long - new value for event
void EventValue::setValue(long newValue){
  value = newValue;
}

// ========= Events =========

// constructor for class Event, event value of an event is OPTIONAL
// argument: event type, timestamp of event, optional eventvalue
Event::Event(std::string const& type, long timestamp, EventValue* const& eventValue):type(type),timestamp(timestamp),eventValue(eventValue){}

Event::Event(std::string const& type, long timestamp): type(type), timestamp(timestamp){}

// copy assignment for class Event
Event::Event(Event const& other){
  *this = other;
}

// overloading = operator for copy assignment
Event& Event::operator=(Event const& other){
  
  this->type = other.type;
  this->timestamp = other.timestamp;
  if(other.eventValue != nullptr){
    this->eventValue = new EventValue(other.eventValue->getValue());
  }
  this->next = other.next;
  return *this;
}

// destructor for class event
Event::~Event(){
  delete eventValue;
}


// getter function for timestamp of an event
// return: long - timestamp
long Event::getTimestamp() const{
  return timestamp;
}

// getter function for type of an event
// return: std::string - type
std::string const& Event::getType() const{
  return type;
}

// check if an event has an event value or not
bool Event::hasValue() const {
  if(eventValue == nullptr){return false;}
  return true;
}

// getter function for value of an event
// return: pointer of EventValue
EventValue* Event::getValue() const{
  return eventValue;
}

// ========= Roast =========

// constructor for class Roast
// argument: long - roast id, long - timestamp of a roast
Roast::Roast(long id, long timestamp):id(id),timestamp(timestamp){}

// overload constructor, used when only has one timestamp argument
Roast::Roast(long timestamp):timestamp(timestamp){}

// copy assignment for class Roast
Roast::Roast(Roast const& other){
  *this = other;
}

// overloading operator = for copy assignment
Roast& Roast::operator=(Roast const& other){
  
  this->id = other.id;
  this->timestamp = other.timestamp;
  this->numIngredients = other.numIngredients;
  this->numEvents = other.numEvents;

  // copy linked lists for Ingredient and Event
  Ingredient* delCurrentIng = ingredient;
  while(delCurrentIng != nullptr){
    Ingredient* delNextIng = delCurrentIng->next;
    delete delCurrentIng;
    delCurrentIng = delNextIng;
  }
  if(other.ingredient != nullptr){
    ingredient = new Ingredient(*other.ingredient); 
    Ingredient* frontIng = ingredient;
    Ingredient* endIng = other.ingredient->next;
    while(endIng != nullptr){
      frontIng->next = new Ingredient(*endIng);
      frontIng = frontIng->next;
      endIng = endIng->next;
    }
  }
  
  
  Event* delCurrentEvent = event;
  while(delCurrentEvent != nullptr){
    Event* delNextEvent = delCurrentEvent->next;
    delete delCurrentEvent;
    delCurrentEvent = delNextEvent;
  }
  if(other.event != nullptr){
    event = new Event(*other.event);
    Event* frontEvent = event;
    Event* endEvent = other.event->next;
    while(endEvent != nullptr){
      frontEvent->next = new Event(*endEvent);
      frontEvent = frontEvent->next;
      endEvent = endEvent->next;
    }
  }

  return *this;
}

// destructor for class Roast, delete all the Ingredient and Event on heap
Roast::~Roast(){
  Ingredient* delCurrentIng = ingredient;
  while(delCurrentIng != nullptr){
    Ingredient* delNextIng = delCurrentIng->next;
    delete delCurrentIng;
    delCurrentIng = delNextIng;
  }

  Event* delCurrentEvent = event;
  while(delCurrentEvent != nullptr){
    Event* delNextEvent = delCurrentEvent->next;
    delete delCurrentEvent;
    delCurrentEvent = delNextEvent;
  }
}

// getter function for roast id
// return: long - id
long Roast::getId() const{
  return id;
}

// getter funciton for timestamp of a roast
// return: long - timestamp
long Roast::getTimestamp() const{
  return timestamp;
}

// getter function for a ingredient in a roast
// argument: index of the ingredient
// return: the ingredient object
Ingredient& Roast::getIngredient(int i){
  if(ingredient != nullptr){
    Ingredient* getIng = ingredient;
    int count = 0;
    while(getIng != nullptr && count < numIngredients){
      if(count == i){
	return *getIng;
      }
      count++;
      getIng = getIng->next;
    }
  }

  std::cerr << "Invalid index for ingredient in roast :" << i << std::endl;
  exit(1);
}

Ingredient const& Roast::getIngredient(int i) const{
  if(ingredient != nullptr){
    Ingredient* getIng = ingredient;
    int count = 0;
    while(getIng != nullptr && count < numIngredients){
      if(count == i){
	return *getIng;
      }
      count++;
      getIng = getIng->next;
    }
  }

  std::cerr << "Invalid index for ingredient in roast :" << i << std::endl;
  exit(1);
}


// getter funciton for the total number of ingredients in a roast
// return: number of ingredients
int Roast::getIngredientsCount() const{
  return numIngredients;
}


// adding an ingredient to linked list of Ingredient in a roast
// argument: the new ingredient object
void Roast::addIngredient(Ingredient const& newIngredient){
  // set new object to head node if there isn't any
  if(ingredient == nullptr){
    ingredient = new Ingredient(newIngredient);
  }
  else{
    Ingredient* endIng = ingredient;
    while(endIng->next != nullptr){              // iterate to end
      endIng = endIng->next;
    }
    endIng->next = new Ingredient(newIngredient);// add to end of list
  }
  
  numIngredients++;
}



// getter funciton for event in roast
// argument: index of the event
// return: the event object
Event const& Roast::getEvent(int i) const{
  if(event != nullptr){
    Event* getEvent = event;
    int count = 0;
    while(getEvent != nullptr && count < numEvents){
      if(count == i){
	return *getEvent;
      }
      count++;
      getEvent = getEvent->next;
    }
  }
  std::cerr << "Invalid index for event in roast: " << i << std::endl;
  exit(1);
}


// get an event by its timestamp
// argument: timestamp of the event
// return: event object
Event const& Roast::getEventByTimestamp(long ts) const{
  if(event != nullptr){
    Event* getEvent = event;
    int count = 0;
    while(getEvent != nullptr && count < numEvents){
      if(getEvent->getTimestamp() == ts){
	return *getEvent;
      }
      count++;
      getEvent = getEvent->next;
    }
  }
  exit(1);
}

// getter for number of events in a roast
// return: int - number of events
int Roast::getEventCount() const{
  return numEvents;
}

// add a new event to the linked list
// argument: new event object
void Roast::addEvent(Event const& newEvent){
  if(event == nullptr){
    event = new Event(newEvent);
  }
  else{
    Event* endEvent = event;
    while(endEvent->next != nullptr){
      endEvent = endEvent->next;
    }
    endEvent->next = new Event(newEvent);
  }

  numEvents++;
}


// remove an event by its timestamp
// argument: timestamp of the event
void Roast::removeEventByTimestamp(long ts){
  if(event == nullptr){
    return;
  }

  Event* delCurrentEvent = event;
  Event* delLastEvent = nullptr;
  while(delCurrentEvent != nullptr){
    if(delCurrentEvent->getTimestamp() == ts){
      if(delLastEvent == nullptr){
	event = delCurrentEvent->next;
      }
      else{
	delLastEvent->next = delCurrentEvent->next;
      }
      delete delCurrentEvent;
      numEvents--;
      break;
    }
    delLastEvent = delCurrentEvent;
    delCurrentEvent = delCurrentEvent->next;
  }
}

// remove an ingrdient by bean name
// argument: std::string - beanName
void Roast::removeIngredientByBeanName(std::string const& beanName){
  if(ingredient == nullptr){
    return;
  }

  Ingredient* delCurrentIng = ingredient;
  Ingredient* delLastIng = nullptr;
  while(delCurrentIng != nullptr){
    if(delCurrentIng->getBean().getName() == beanName){
      if(delLastIng == nullptr){
	ingredient = delCurrentIng->next;
      }
      else{
	delLastIng->next = delCurrentIng->next;
      }
      delete delCurrentIng;
      numIngredients--;
      return;
    }
    delLastIng = delCurrentIng;
    delCurrentIng = delCurrentIng->next;
  }

}


