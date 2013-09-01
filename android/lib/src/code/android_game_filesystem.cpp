/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the rp::android_game_filesystem class.
 * \author Julien Jorge
 */
#include "android_game_filesystem.hpp"

#include <SDL/SDL_system.h>

#include <claw/logger.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param game_name The name of the game
 */
rp::android_game_filesystem::android_game_filesystem
( std::string game_name )
  : bear::engine::default_game_filesystem( game_name, get_android_root() )
{
  claw::logger << claw::log_verbose << "Internal storage is '"
               << get_android_root() << std::endl;
} // android_game_filesystem::android_game_filesystem()

/*----------------------------------------------------------------------------*/
/**
 * \brief Creates a dynamically allocated copy of this instance.
 */
rp::android_game_filesystem*
rp::android_game_filesystem::clone() const
{
  return new android_game_filesystem( *this );
} // android_game_filesystem::clone()

/*----------------------------------------------------------------------------*/
/**
 * \brief Gets the root directory where the application can write its files.
 */
std::string rp::android_game_filesystem::get_android_root() const
{
  return SDL_AndroidGetInternalStoragePath();
} // android_game_filesystem::get_android_root()
