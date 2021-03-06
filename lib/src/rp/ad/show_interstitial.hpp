/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
#ifndef __RP_SHOW_INTERSTITIAL_HPP__
#define __RP_SHOW_INTERSTITIAL_HPP__

#include <boost/signals2/connection.hpp>

namespace rp
{
  enum class ad_location
  {
    level_completed,
    restart_level
  };
  
  boost::signals2::connection show_interstitial
  ( ad_location location, const boost::function< void() >& callback );
}

#endif
