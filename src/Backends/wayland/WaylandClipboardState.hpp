#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>
#include <wayland-client.h>

namespace gamescope {

struct CWaylandDataOffer {
	wl_data_offer* m_pOffer;
	int m_fd;
};

struct CWaylandClipboardState {
	std::thread m_ClipboardReadThread;
	std::condition_variable m_PendingOffersCV;
	std::mutex m_PendingOffersMutex;
	std::queue<CWaylandDataOffer> m_PendingOffers;
	std::atomic<bool> m_ClipboardThreadRunning = {false};

	~CWaylandClipboardState();
};

} // namespace gamescope
