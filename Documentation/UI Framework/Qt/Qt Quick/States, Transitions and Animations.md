

    AnchorChanges                   Specifies how to change the anchors of an item in a state
    ParentChange                    Specifies how to reparent an Item in a state change
    PropertyChanges                 Describes new property bindings or values for a state
    State                           Defines configurations of objects and properties
    StateChangeScript               Specifies how to run a script in a state
    StateGroup                      Provides built-in state support for non-Item types


State:
Transition:
Animation子类:    
    SequentialAnimation
    ParallelAnimation
    PauseAnimation    
    ScriptAction
    PropertyAction
    AnchorAnimation         Animates changes in anchor values
    ColorAnimation          Animates changes in color values
    NumberAnimation         Animates changes in qreal-type values
    ParentAnimation         Animates changes in parent values
    PathAnimation           Animates an item along a path
    PropertyAnimation       Animates changes in property values
        SmoothedAnimation
        SpringAnimation
    RotationAnimation       Animates changes in rotation values
    Vector3dAnimation       Animates changes in QVector3d values
