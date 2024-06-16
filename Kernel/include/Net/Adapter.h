/*
Implement a network adapter interface to manage :
basic operation, state and packet processing of network devices.
*/
#pragma once
#include <Device.h>
#include <Net/Net.h>
#include <Scheduler.h>

enum {
    LinkDown,
    LinkUp,
};

class IPSocket;
namespace Network {
    class NetworkAdapter : public Device {
        friend class NetFS;
    public:
        enum AdapterType {
            NetworkAdapterLoopback,
            NetworkAdapterEthernet,
        };

        enum DriverState {
            OK,
            Uninitialized,
            Error,
        };
        DriverState dState = Uninitialized;

        MACAddress mac;

        // All of these are big-endian
        IPv4Address adapterIP = 0; // 0.0.0.0
        IPv4Address gatewayIP = 0; // 0.0.0.0
        IPv4Address subnetMask = 0xFFFFFFFF; // 255.255.255.255 (no subnet)
        int adapterIndex = 0; // Index in the adapters list

        NetworkAdapter(AdapterType aType);

        virtual int Ioctl(uint64_t cmd, uint64_t arg);//Handles IO control of devices

        virtual void SendPacket(void* data, size_t len);

        virtual int GetLink() const;
        virtual int QueueSize() const;

        virtual NetworkPacket* Dequeue();//Remove a packet from the queue
        virtual NetworkPacket* DequeueBlocking();//Removes a packet from the queue and blocks if the queue is empty.
        virtual void CachePacket(NetworkPacket* pkt);//cache the packet

        void BindToSocket(IPSocket* sock);//Bind the socket to the adapter
        void UnbindSocket(IPSocket* sock);//Unbind the socket
        void UnbindAllSockets();//Unbind all socket

        virtual ~NetworkAdapter() = default;

    protected:
        static int nextDeviceNumber;//Assign a unique device number to each adapter
        unsigned maxCache = 256; // Maximum amount of cached packets, NIC drivers are free to change this

        int linkState = LinkDown;

        FastList<NetworkPacket*> cache;//List of cached packets
        FastList<NetworkPacket*> queue;//The queue of packets to be processed

        Semaphore packetSemaphore = Semaphore(0);

        lock_t cacheLock = 0;
        lock_t queueLock = 0;
        lock_t threadLock = 0;        
        lock_t boundSocketsLock = 0;
        //Lock variable, used for multi-thread synchronization

        AdapterType type;

        List<class ::IPSocket*> boundSockets; // If an adapter is destroyed, we need to know what sockets are bound to it
    };//NetworkAdapterclass

    void AddAdapter(NetworkAdapter* a);
}