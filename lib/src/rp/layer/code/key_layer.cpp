/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.
*/
/**
 * \file
 * \brief Implementation of the rp::help_layer class.
 * \author Julien Jorge
 */
#include "rp/layer/key_layer.hpp"

#include "rp/game_key.hpp"

#include "engine/level.hpp"
#include "engine/level_globals.hpp"
#include "gui/button.hpp"
#include "gui/callback_function.hpp"
#include "input/keyboard.hpp"

#include <boost/bind.hpp>

/*----------------------------------------------------------------------------*/
/**
 * \brief Constructor.
 * \param name The name of the layer.
 */
rp::key_layer::key_layer( const std::string& name )
  : bear::communication::messageable(name), m_visible(false)
{

} // key_layer::key_layer()

/*----------------------------------------------------------------------------*/
/**
 * \brief Initialize the layer.
 */
void rp::key_layer::build()
{
  super::build();

  m_root_window.set_size( get_size() );
  m_root_window.set_background_color( bear::visual::color("#3b3b3b") );
  m_root_window.set_top_left_border_color( bear::visual::color("#a0a0a0") );
  m_root_window.set_bottom_right_border_color( bear::visual::color("#1b1b1b") );

  create_components();

  m_root_window.fit( 10 );
  m_root_window.set_left( ( get_size().x - m_root_window.width() ) / 2 );
  m_root_window.set_bottom( ( get_size().y - m_root_window.height() ) / 2 );

  get_level_globals().register_item(*this);
} // key_layer::build()

/*----------------------------------------------------------------------------*/
/**
 * \brief Inform the layer that a key has been pressed.
 * \param key The value of the pressed key.
 */
bool rp::key_layer::key_pressed( const bear::input::key_info& key )
{
  if ( !m_visible )
    return false;

  bool result = true;

  if ( key.get_code() == bear::input::keyboard::kc_escape )
    hide();
  else if ( key.is_enter() )
    validate();
  else
    result = false;

  return result;
} // key_layer::key_pressed()

/*----------------------------------------------------------------------------*/
/**
 * \brief Shows the dialog.
 */
void rp::key_layer::show()
{
  m_visible = true;

  set_root_component( &m_root_window );
  get_level().set_pause();
} //  key_layer::show()

/*----------------------------------------------------------------------------*/
/**
 * \brief Hides the dialog.
 */
void rp::key_layer::hide()
{
  m_visible = false;

  set_root_component( NULL );
  get_level().unset_pause();
} //  key_layer::hide()

/*----------------------------------------------------------------------------*/
/**
 * \brief Creates the dialog in which the user can enter his code.
 */
void rp::key_layer::create_components()
{
  create_key_text();
  create_validate_button();
  create_cancel_button();
} // key_layer::create_components()

/*----------------------------------------------------------------------------*/
/**
 * \brief Creates the text area where the user can enter his code. 
 */
void rp::key_layer::create_key_text()
{
  const claw::graphic::rgba_pixel color( "#a0a0a0");

  m_key_text =
    new bear::gui::text_input
    ( get_level_globals().get_font( "font/fontopo/fontopo-small.fnt", 20 ),
      color );

  m_key_text->set_border_color( color );
  m_key_text->set_width( 200 );

  m_key_text->add_enter_callback
    ( bear::gui::callback_function_maker
      ( boost::bind( &key_layer::validate, this ) ) );

  m_root_window.insert( m_key_text );
} // key_layer::create_key_text()

/*----------------------------------------------------------------------------*/
/**
 * \brief Creates the button to click to validate the key.
 */
void rp::key_layer::create_validate_button()
{

} // key_layer::create_validate_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Creates the button to click to cancel.
 */
void rp::key_layer::create_cancel_button()
{

} // key_layer::create_cancel_button()

/*----------------------------------------------------------------------------*/
/**
 * \brief Validates the code and hide the frame if it is valid.
 */
void rp::key_layer::validate()
{
  if ( game_key::is_valid_key( m_key_text->get_text() ) )
    {
      game_key::save( m_key_text->get_text() );
      hide();
    }
} //  key_layer::hide()
