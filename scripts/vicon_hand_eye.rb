#! /usr/bin/env ruby

require 'orocos'
require 'vizkit'
include Orocos

if !ARGV[0]
    STDERR.puts "usage: vicon_hand_eye <data_log_directory>"
    exit 1
end

ENV['PKG_CONFIG_PATH'] = "#{File.expand_path("..", File.dirname(__FILE__))}/build:#{ENV['PKG_CONFIG_PATH']}"

Orocos.initialize

Orocos.run 'vicon::Task' => 'vicon_hand_eye' do

    ## Get the Logger
    logger = Orocos.name_service.get 'vicon_hand_eye_Logger'
    logger.file = "vicon_hand_eye.0.log"

    Orocos.conf.load_dir('../config')

    vicon = TaskContext.get 'vicon_hand_eye'
    Orocos.conf.apply(vicon, ['vicon_hand_eye'], :override => true)
    vicon.configure

    #Logger
    logger.log(vicon.pose_samples, 100)

    # logs files
    log_replay = Orocos::Log::Replay.open( ARGV[0] )

    # log port connections
    log_replay.vicon.pose_samples.connect_to(vicon.pose_samples_in, :type => :buffer, :size => 200)

    # Start the logger and vicon
    logger.start
    vicon.start

    # open the log replay widget
    control = Vizkit.control log_replay
    control.speed = 1

    Vizkit.exec
end
