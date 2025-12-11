#include "ALListener.h"

ALListener::ALListener() {

}

ALListener::~ALListener() {

}

void ALListener::SetGain(float Value) {
    alListenerf(AL_GAIN, Value);
}

void ALListener::SetPosition(float X, float Y, float Z) {
    alListener3f(AL_POSITION, X, Y, Z);
}

void ALListener::SetVelocity(float X, float Y, float Z) {
    alListener3f(AL_VELOCITY, X, Y, Z);
}

void ALListener::SetOrientation(float AT_X, float AT_Y, float AT_Z, float UP_X, float UP_Y, float UP_Z) {
    ALfloat Values[] = {AT_X, AT_Y, AT_Z, UP_X, UP_Y, UP_Z};
    alListenerfv(AL_ORIENTATION, Values);
}