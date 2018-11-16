#include <fstream>
#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/netanim-module.h"
#include "ns3/mobility-module.h"
#include <bits/stdc++.h>


using namespace ns3;
using namespace std;

NS_LOG_COMPONENT_DEFINE ("ring");


int main (int argc, char *argv[])
{
	Time::SetResolution (Time::NS);
	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
	int n;
	cout<<"Enter the number of nodes in the ring(>3)"<<endl;
	cin>>n;
	if(n<3)
		n=3;
	NodeContainer nd;
	nd.Create(n);
	
	PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));
	
	vector<NetDeviceContainer> v;
	
	for(int i=0;i<n;i++)
		v.push_back(p2p.Install(nd.Get(i),nd.Get((i+1)%n)));
	InternetStackHelper stack;
	stack.Install(nd);
	vector<Ipv4InterfaceContainer> intf;
	Ipv4AddressHelper address;
	for(int i=0;i<n;i++)
	{
		string s="10.1.";
    s+=((char)'0'+i+1);
    s+=".0";
  	address.SetBase (s.c_str(), "255.255.255.0");
  	intf.push_back(address.Assign(v[i]));
	}
	Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
	UdpEchoServerHelper echoServer(9);
	ApplicationContainer serverApps=echoServer.Install(nd.Get(0));
	UdpEchoClientHelper echoClient(intf[0].GetAddress(0),9);
	echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
  ApplicationContainer clientApps = echoClient.Install (nd.Get (n/2));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));
	clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));
  AnimationInterface anim ("ring.xml");
  double ang=(acos(-1)*2)/n;
  double cx=31.5,cy=47.5;
  for(int i=0;i<n;i++)
  {
  	anim.SetConstantPosition(nd.Get(i),cx+10*cos(i*ang),cy+10*sin(i*ang));
	}
  
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
	
