#include "WaylandClipboardState.hpp"

#include <unistd.h>

namespace gamescope {

CWaylandClipboardState::~CWaylandClipboardState() {
	m_ClipboardThreadRunning = false;
	m_PendingOffersCV.notify_one();

	if (m_ClipboardReadThread.joinable()) {
		m_ClipboardReadThread.join();
	}

	std::lock_guard<std::mutex> lock(m_PendingOffersMutex);
	while (!m_PendingOffers.empty()) {
		auto& offer = m_PendingOffers.front();
		close(offer.m_fd);
		wl_data_offer_destroy(offer.m_pOffer);
		m_PendingOffers.pop();
	}
}

} // namespace gamescope
