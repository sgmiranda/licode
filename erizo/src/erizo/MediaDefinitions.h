/*
 * mediadefinitions.h
 */

#ifndef MEDIADEFINITIONS_H_
#define MEDIADEFINITIONS_H_

namespace erizo{

class NiceConnection;

struct packet{
	char data[1200];
	int length;
};

class FeedbackSink{
public:
  virtual int deliverFeedback(char* buf, int len)=0;
};

class FeedbackSource{
protected:
  FeedbackSink* fbSink_;
public:
  virtual void setFeedbackSink(FeedbackSink* sink){
    fbSink_ = sink;
  };

};

/*
 * A MediaSink 
 */
class MediaSink{
protected:
  //SSRCs received by the SINK
  unsigned int audioSinkSSRC_;
  unsigned int videoSinkSSRC_;
  //Is it able to provide Feedback
  FeedbackSource* sinkfbSource_;
public:
	virtual int deliverAudioData(char* buf, int len)=0;
	virtual int deliverVideoData(char* buf, int len)=0;
  virtual unsigned int getVideoSinkSSRC (){ return videoSinkSSRC_;};
  virtual void setVideoSinkSSRC (unsigned int ssrc){ videoSinkSSRC_ = ssrc;};
  virtual unsigned int getAudioSinkSSRC (){ return audioSinkSSRC_;};
  virtual void setAudioSinkSSRC (unsigned int ssrc){ audioSinkSSRC_ = ssrc;};
  virtual FeedbackSource* getFeedbackSource(){
    return sinkfbSource_;
  };
  virtual void closeSink()=0;
	virtual ~MediaSink(){};
};

/**
 * A MediaSource is any class that produces audio or video data.
 */
class MediaSource{
protected: 
  //SSRCs coming from the source
    unsigned int videoSourceSSRC_;
    unsigned int audioSourceSSRC_;
    MediaSink* videoSink_;
    MediaSink* audioSink_;
  //can it accept feedback
    FeedbackSink* sourcefbSink_;
public:
  virtual void setAudioSink(MediaSink* audioSink){
    this->audioSink_ = audioSink;
  };
  virtual void setVideoSink(MediaSink* videoSink){
    this->videoSink_ = videoSink;
  };

  virtual FeedbackSink* getFeedbackSink(){
    return sourcefbSink_;
  };
  virtual int sendFirPacket()=0;
  virtual unsigned int getVideoSourceSSRC (){ return videoSourceSSRC_;};
  virtual void setVideoSourceSSRC (unsigned int ssrc){ videoSourceSSRC_ = ssrc;};
  virtual unsigned int getAudioSourceSSRC (){ return audioSourceSSRC_;};
  virtual void setAudioSourceSSRC (unsigned int ssrc){ audioSourceSSRC_ = ssrc;};
  virtual void closeSource()=0;
	virtual ~MediaSource(){};
};

/**
 * A NiceReceiver is any class that can receive data from a nice connection.
 */
class NiceReceiver{
public:
	virtual int receiveNiceData(char* buf, int len, NiceConnection* nice)=0;
	virtual ~NiceReceiver(){};
};

} /* namespace erizo */

#endif /* MEDIADEFINITIONS_H_ */