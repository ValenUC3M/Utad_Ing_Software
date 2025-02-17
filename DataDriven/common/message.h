#pragma once
#include "vector2d.h"

// base class for messages
class Message 
{ 
public:
    virtual ~Message(){}
};

// base class for collision messages
class CollisionMessage : public Message
{
public:
    CollisionMessage(vec2 _newPos) : newPos(_newPos) {}
    vec2 newPos;
};

// collision with entity
class EntCollisionMessage : public CollisionMessage
{
public:
    EntCollisionMessage(vec2 _newPos) : CollisionMessage(_newPos) {}
};

// collision with world limits
class LimitWorldCollMessage : public CollisionMessage
{
public:
    LimitWorldCollMessage(vec2 _newDirection, vec2 _newPos) : 
        CollisionMessage(_newPos), entityDirection(_newDirection) {}

    vec2 entityDirection; //{ Horizontal, Vertical }
};

// new position message
class NewPositionMessage : public Message
{
public:
    NewPositionMessage(vec2 _newPos) : newPos(_newPos) {}
    vec2 newPos;
};
