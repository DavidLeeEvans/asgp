/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
/**
 * \file
 * \brief Implementation of the bear::engine::item_that_speaks class.
 * \author Sebastien Angibaud
 */

#include "engine/level_globals.hpp"

#include "rp/defines.hpp"

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 */
template<class Base>
rp::item_that_speaks<Base>::item_that_speaks()
  : super( RP_BALLOON_LAYER_DEFAULT_TARGET_NAME )
{

} // item_that_speaks::item_that_speaks()

/*----------------------------------------------------------------------------*/
/**
 * \brief Load the media required by this class.
 */
template<class Base>
void rp::item_that_speaks<Base>::pre_cache()
{
  super::pre_cache();

  this->get_level_globals().load_font("font/fontopo/fontopo-small.fnt");
  this->get_level_globals().load_image("gfx/speech/balloon-1.png");
} // item_that_speaks::pre_cache()

/*---------------------------------------------------------------------------*/
/**
 * \brief Initializes the item once that it is in a level.
 */
template<class Base>
void rp::item_that_speaks<Base>::build()
{
  super::build();

  this->get_balloon().set_spike_sprite
    ( this->get_level_globals().auto_sprite
      ("gfx/speech/balloon-1.png", "spike") );
  this->get_balloon().set_corner_sprite
    ( this->get_level_globals().auto_sprite
      ("gfx/speech/balloon-1.png", "corner") );

  this->get_balloon().set_horizontal_border_sprite
    ( this->get_level_globals().auto_sprite
      ( "gfx/speech/balloon-1.png", "horizontal border" ) );
  this->get_balloon().set_vertical_border_sprite
    ( this->get_level_globals().auto_sprite
      ( "gfx/speech/balloon-1.png", "vertical border" ) );

  this->get_balloon().set_font
    ( this->get_level_globals().get_font("font/fontopo/fontopo-small.fnt",20) );
} // item_that_speaks::build()
