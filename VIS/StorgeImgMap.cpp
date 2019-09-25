#include "StorgeImgMap.h"
#include <mutex>

std::mutex mutexlock_sim;

StorgeImgMap::StorgeImgMap(void)
{
	this->Imgmaps=new map<long,ChannelImg *>();
	this->flag=0;
}


StorgeImgMap::~StorgeImgMap(void)
{
}

void StorgeImgMap::add( long lRealHandle, cv::Mat img)
{
	std::unique_lock<std::mutex> ulk(mutexlock_sim);
	ChannelImg * changeImg=this->Imgmaps->find(lRealHandle)->second;
	changeImg->setCount(1);
	changeImg->setImg(img);
}

map<long, cv::Mat> StorgeImgMap::getImg( long IRlRealHandle,long RGBRealHanle )
{
	map<long, cv::Mat> imgmat;
	if(IRlRealHandle!=-1&&RGBRealHanle!=-1){
		
		ChannelImg * irChangeImg=this->Imgmaps->find(IRlRealHandle)->second;
		ChannelImg * rgbChangeImg=this->Imgmaps->find(RGBRealHanle)->second;

		if (irChangeImg->getCount() == 1) 
		{
			std::unique_lock<std::mutex> ulk(mutexlock_sim);
			irChangeImg->setCount(0);
			imgmat.insert(make_pair(IRlRealHandle, irChangeImg->getImg()));
		}
		if (rgbChangeImg->getCount() == 1) {
		
			std::unique_lock<std::mutex> ulk(mutexlock_sim);
			rgbChangeImg->setCount(0);
			imgmat.insert(make_pair(RGBRealHanle, rgbChangeImg->getImg()));
		}
		/*if(irChangeImg->getCount()==1&& rgbChangeImg->getCount() == 1)
		{
			std::unique_lock<std::mutex> ulk(mutexlock_sim);
			ec::Time now;
			RgbMonitor.find(RGBRealHanle)->second.setSeconds(now.getUTCFullSeconds());
			RgbMonitor.find(RGBRealHanle)->second.setMicroSeconds(now.tv_usec());	
			irChangeImg->setCount(0);
			rgbChangeImg->setCount(0);
			imgmat.insert(make_pair(IRlRealHandle, irChangeImg->getImg()));
			imgmat.insert(make_pair(RGBRealHanle, rgbChangeImg->getImg()));
		}
		else 
		{
			ec::Time time;
			long timespan = time.diff(RgbMonitor.find(RGBRealHanle)->second, ec::Duration::Second);
			//如果rgb 5s 都没有数据  就直接返回ir;
			if (irChangeImg->getCount() == 0)
				  return imgmat;
			if (irChangeImg->getCount() == 1 && timespan > 5)
			{
				std::unique_lock<std::mutex> ulk(mutexlock_sim);
				irChangeImg->setCount(0);
				imgmat.insert(make_pair(IRlRealHandle, irChangeImg->getImg()));
			}
		}*/
	}
	else if(IRlRealHandle!=-1&&RGBRealHanle==-1)
	{
	    ChannelImg * irChangeImg=this->Imgmaps->find(IRlRealHandle)->second;
		if(irChangeImg->getCount()==0)
			return imgmat;
		std::unique_lock<std::mutex> ulk(mutexlock_sim);
		irChangeImg->setCount(0);
		imgmat.insert(make_pair(IRlRealHandle, irChangeImg->getImg()));
	
	}else{
	   ChannelImg * rgbChangeImg=this->Imgmaps->find(RGBRealHanle)->second;
	   if(rgbChangeImg->getCount()==0)
			return imgmat;
	    std::unique_lock<std::mutex> ulk(mutexlock_sim);
		rgbChangeImg->setCount(0);
		imgmat.insert(make_pair(RGBRealHanle,rgbChangeImg->getImg()));
	}
	return imgmat;

}

cv::Mat StorgeImgMap::getImg( long IRlRealHandle )
{
	std::unique_lock<std::mutex> ulk(mutexlock_sim);
	return this->Imgmaps->find(IRlRealHandle)->second->getImg();
}
