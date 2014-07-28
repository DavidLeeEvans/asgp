/*
  Copyright (C) 2012 Stuffomatic Ltd. <contact@stuff-o-matic.com>

  All rights reserved.

  See the accompanying license file for details about usage, modification and
  distribution of this file.
*/
package com.stuffomatic.asgp;

import org.libsdl.app.SDLActivity;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import android.widget.RelativeLayout;

import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.AdListener;

public class ASGP extends SDLActivity
{
    /**
     * The view displaying the ads when the game tells us to.
     */
    private AdView mAdView;

    static {
        System.loadLibrary( "gnustl_shared" );
        System.loadLibrary( "andy-super-great-park" );
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        createAdView();
        hideAds();

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        hideActionBars();
        addVisibilityChangeListener();
    } // onCreate()

    /**
     * Tells the system to open a given URL.
     * @param url The URL to open.
     */
    public void openUrl( String url ) {

        final Intent browserIntent =
            new Intent( Intent.ACTION_VIEW, Uri.parse(url) );
        startActivity(browserIntent);
    } // openUrl()

    /**
     * Tells the system to show the home screen.
     */
    public void showHome() {

        final Intent homeIntent = new Intent( Intent.ACTION_MAIN );
        homeIntent.addCategory( Intent.CATEGORY_HOME );
        startActivity(homeIntent);
    } // showHome()

    /**
     * Returns the name of the device on which the game is running.
     */
    public String getDeviceModelName() {
        
        return Build.MANUFACTURER + ", " + Build.PRODUCT + ", " + Build.MODEL;
    } // getDeviceModelName()

    /**
     * Makes the ad banner visible.
     */
    public void showAds() {
        
        setAdsVisibility( View.VISIBLE );
    } // showAds()

    /**
     * Hides the ad banner.
     */
    public void hideAds() {
        
        setAdsVisibility( View.INVISIBLE );
    } // hideAds()

    @Override
    public void onPause() {
        mAdView.pause();
        super.onPause();
    } // onPause()

    @Override
    public void onResume() {
        super.onResume();
        mAdView.resume();
        hideActionBars();
    } // onResume()

    @Override
    public void onDestroy() {
        mAdView.destroy();
        super.onDestroy();
    } // onDestroy()

    @Override
    public void onWindowFocusChanged( boolean hasFocus ) {
        super.onWindowFocusChanged( hasFocus );
        if ( hasFocus ) {
            hideActionBars();
        }
    }

    /**
     * Hides the action bar such that the game uses the full screen.
     */
    private void hideActionBars() {

        getWindow().getDecorView().setSystemUiVisibility
            ( View.SYSTEM_UI_FLAG_LOW_PROFILE
              | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
              | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
              | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
              | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
              | View.SYSTEM_UI_FLAG_FULLSCREEN
              | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY );
    } // hideActionBars()

    /**
     * Adds an event listener of the UI visibility changes, that will hide the
     * action bars when they have been shown due to an external event.
     */
    private void addVisibilityChangeListener() {

        final View decorView = getWindow().getDecorView();

        decorView.setOnSystemUiVisibilityChangeListener
            ( new View.OnSystemUiVisibilityChangeListener() {
                @Override
                public void onSystemUiVisibilityChange( int visibility ) {
        
                    if ( (visibility & View.SYSTEM_UI_FLAG_FULLSCREEN) == 0 ) {
                        hideActionBars();
                    }
                }
            } );
    } // addVisibilityChangeListener()

    /**
     * Creates mAdView and inserts it in the layout.
     */
    private void createAdView() {

        // Create the adView.
        mAdView = new AdView( this );
        
        mAdView.setAdUnitId( "ca-app-pub-8517534578027121/5449175693" );
        mAdView.setAdSize( AdSize.BANNER );

        RelativeLayout layout = new RelativeLayout( getContext() );
        layout.setGravity( Gravity.RIGHT | Gravity.BOTTOM );

        layout.setLayoutParams
            ( new RelativeLayout.LayoutParams
              ( RelativeLayout.LayoutParams.FILL_PARENT,
                RelativeLayout.LayoutParams.FILL_PARENT ) );

        layout.addView(mAdView);

        mLayout.addView( layout );

        requestAd();
    } // createAdView()

    /**
     * Requests an ad to the ad server.
     */
    private void requestAd() {

        // Initiate a generic request.
        AdRequest adRequest =
            new AdRequest.Builder()
            .addTestDevice( AdRequest.DEVICE_ID_EMULATOR )
            .build();

        // Load the adView with the ad request.
        mAdView.loadAd(adRequest);
    } // createAdView()

    /**
     * Changes the visibility of the ads.
     * @param visibility The new visibility, like View.VISIBLE, View.INVISIBLE.
     */
    private void setAdsVisibility( final int visibility ) {

        final AdView view = mAdView;

        runOnUiThread( new Runnable() {

            @Override
            public void run() {

                try {
                    mAdView.setVisibility( visibility );
                } catch ( Throwable e ) {
                    Log.e( "ASGP-J", e.getMessage() );
                }
            }
        } );
    } // setAdsVisibility()

}
