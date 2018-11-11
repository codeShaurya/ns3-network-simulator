#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create (5);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices1;
  devices1 = pointToPoint.Install (nodes.Get(0),nodes.Get(1));
  NetDeviceContainer devices2;
  devices2 = pointToPoint.Install (nodes.Get(1),nodes.Get(2));
  NetDeviceContainer devices3;
  devices3 = pointToPoint.Install (nodes.Get(2),nodes.Get(3));
  NetDeviceContainer devices4;
  devices4 = pointToPoint.Install (nodes.Get(3),nodes.Get(4));
  NetDeviceContainer devices5;
  devices5 = pointToPoint.Install (nodes.Get(4),nodes.Get(0));

  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address1;
  address1.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces1 = address1.Assign (devices1);

  address1.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces2 = address1.Assign (devices2);

  address1.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces3 = address1.Assign (devices3);

  address1.SetBase ("10.1.4.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces4 = address1.Assign (devices4);

  address1.SetBase ("10.1.5.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces5 = address1.Assign (devices5);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  ApplicationContainer serverApps2 = echoServer.Install (nodes.Get (2));
  serverApps2.Start (Seconds (1.0));
  serverApps2.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (interfaces1.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (2));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient2 (interfaces3.GetAddress (0), 9);
  echoClient2.SetAttribute ("MaxPackets", UintegerValue (2));
  echoClient2.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient2.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps2 = echoClient2.Install (nodes.Get (4));
  clientApps2.Start (Seconds (2.0));
  clientApps2.Stop (Seconds (10.0));
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  AnimationInterface anim("ring.xml");
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
