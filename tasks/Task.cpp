/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"

using namespace vicon;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::~Task()
{
}

::base::samples::RigidBodyState Task::getZeroOrigin()
{
    base::samples::RigidBodyState lrbs;
    lrbs.initUnknown();
    return lrbs;
}

void Task::pose_samples_inCallback(const base::Time &ts, const ::base::samples::RigidBodyState &pose_samples_in_sample)
{
    ::base::samples::RigidBodyState pose_samples_out = pose_samples_in_sample;
    Eigen::Affine3d T_hand_eye( Eigen::Affine3d(_body_reference.value()) );

    pose_samples_out.setTransform(pose_samples_in_sample.getTransform() * T_hand_eye);
    _pose_samples.write(pose_samples_out);
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;

    if (!_body_reference.value().hasValidPosition() || !_body_reference.value().hasValidOrientation() ) 
        _body_reference.set(getZeroOrigin());

    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}
