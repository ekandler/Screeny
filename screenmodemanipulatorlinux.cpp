#include "screenmodemanipulatorlinux.h"
#include<iostream>

extern "C" {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-pedantic"
#pragma GCC diagnostic ignored "-fpermissive"
#define VERSION "1.4.3"
#define main screen_main
#include "xrandr.h"
#undef main
#pragma GCC diagnostic pop
}
// Xrandr copy implementation
/*
 *
#include<X11/Xlib.h>
#include<X11/extensions/Xrandr.h>
 *  Display                 *dpy;
    Window                  root;
    int                     num_sizes;
    XRRScreenSize           *xrrs;
    XRRScreenConfiguration  *conf;
    short                   possible_frequencies[64][64];
    short                   original_rate;
    Rotation                original_rotation;
    SizeID                  original_size_id;

    dpy    = XOpenDisplay("");
    root   = RootWindow(dpy, 0);
    //
    //     GET POSSIBLE SCREEN RESOLUTIONS
    //

     //
     //     GET CURRENT RESOLUTION AND FREQUENCY

    XRRScreenResources * res = XRRGetScreenResourcesCurrent (dpy, root);
    std::cout << res->ncrtc;

    for (int o = 0; o < res->noutput; o++) {
        XRROutputInfo *output_info = XRRGetOutputInfo (dpy, res, res->outputs[o]);
        std::cout << output_info->name << std::endl;

        for(int i=0; i < output_info->nmode; i++) {
//            XRRModeInfo	*mode = find_mode_by_xid (output_info->modes[i]);
//            std::cout << mode->name << std::endl;
        }



    }

    for (int i = 0; i<res->nmode; i++) {
        XRRModeInfo *mode = &res->modes[i];
        std::cout << mode->name << " " << mode->vTotal << std::endl;
    }

    XRROutputInfo *output_info = XRRGetOutputInfo (dpy, res, res->outputs[0]);
    XRRCrtcInfo *crtcinfo = XRRGetCrtcInfo(dpy, res, output_info->crtc);




    xrrs   = XRRSizes(dpy, 0, &num_sizes);
    for(int i = 0; i < num_sizes; i ++) {
            short   *rates;
            int     num_rates;

            printf("\n\t%2i : %4i x %4i   (%4imm x%4imm ) ", i, xrrs[i].width, xrrs[i].height, xrrs[i].mwidth, xrrs[i].mheight);

            rates = XRRRates(dpy, 0, i, &num_rates);

            for(int j = 0; j < num_rates; j ++) {
                    possible_frequencies[i][j] = rates[j];
                    printf("%4i ", rates[j]); } }

     printf("\n");

    //set_output_info

     //
//     conf                   = XRRGetScreenInfo(dpy, root);
//     original_rate          = XRRConfigCurrentRate(conf);
//     original_size_id       = XRRConfigCurrentConfiguration(conf, &original_rotation);

//     printf("\n\tCURRENT SIZE ID  : %i\n", original_size_id);
//     printf("\tCURRENT ROTATION : %i \n", original_rotation);
//     printf("\tCURRENT RATE     : %i Hz\n\n", original_rate);
     //
     //     CHANGE RESOLUTION
     //
//     printf("\tCHANGED TO %i x %i PIXELS, %i Hz\n\n", xrrs[1].width, xrrs[1].height, possible_frequencies[1][0]);
//     XRRSetScreenConfigAndRate(dpy, conf, root, 1, RR_Rotate_0, possible_frequencies[1][0], CurrentTime);
//     //
//     //     SLEEP A WHILE
//     //
//     usleep(6000000);
//     //
//     //     RESTORE ORIGINAL CONFIGURATION
//     //
//     printf("\tRESTORING %i x %i PIXELS, %i Hz\n\n", xrrs[original_size_id].width, xrrs[original_size_id].height, original_rate);
//     XRRSetScreenConfigAndRate(dpy, conf, root, original_size_id, original_rotation, original_rate, CurrentTime);
     //

    XCloseDisplay(dpy);
    */


// most code copied and modified from xrandr implementation
void ScreenModeManipulatorLinux::SearchAvailableScreens()
{

    int		event_base, error_base;
    int		major, minor;
    const char * display = NULL;
    int screen = 0;

    dpy = XOpenDisplay (display);
    if (dpy == NULL) {
        fprintf (stderr, "Can't open display NULL\n");
        exit (1);
    }
    root = RootWindow (dpy, screen);

    if (!XRRQueryExtension (dpy, &event_base, &error_base) ||
        !XRRQueryVersion (dpy, &major, &minor))
    {
    fprintf (stderr, "RandR extension missing\n");
    exit (1);
    }
    if (major > 1 || (major == 1 && minor >= 2))
    has_1_2 = True;
    if (major > 1 || (major == 1 && minor >= 3))
    has_1_3 = True;
    if (major > 1 || (major == 1 && minor >= 4))
    has_1_4 = True;
    if (major > 1 || (major == 1 && minor >= 5))
    has_1_5 = True;

    //std::cout << exec("xrandr");

    get_screen (True);
    get_crtcs ();
    get_outputs ();

    output_t    *output;
    int	    m;
    int screenID = -1;

    printf ("Screen %d: minimum %d x %d, current %d x %d, maximum %d x %d\n",
    screen, minWidth, minHeight,
    DisplayWidth (dpy, screen), DisplayHeight(dpy, screen),
    maxWidth, maxHeight);

    for (output = all_outputs; output; output = output->next)
    {
        screenID++;
        QVector<ScreenMode> screeny_modes;
        int used_mode = -1;
        int mode_i = -1;

        XRROutputInfo   *output_info = output->output_info;
        crtc_t	    *cur_crtc = output->crtc_info;
        XRRCrtcInfo	    *crtc_info = cur_crtc ? cur_crtc->crtc_info : NULL;
        XRRModeInfo	    *cur_mode = output->mode_info;
        Atom	    *props;
        int		    j, nprop;
        Bool	    *mode_shown;
        Rotation	    rotations = output_rotations (output);

        printf ("%s %s", output_info->name, connection[output_info->connection]);
        if (output->primary) {
        printf(" primary");
        }
        if (cur_mode)
        {
        if (crtc_info) {
            printf (" %dx%d+%d+%d",
                crtc_info->width, crtc_info->height,
                crtc_info->x, crtc_info->y);
        } else {
            printf (" %dx%d+%d+%d",
                cur_mode->width, cur_mode->height, output->x,
                output->y);
        }
            printf (" (0x%x)", (int)cur_mode->id);
        if (output->rotation != RR_Rotate_0 || verbose)
        {
            printf (" %s",
                rotation_name (output->rotation));
            if (output->rotation & (RR_Reflect_X|RR_Reflect_Y))
            printf (" %s", reflection_name (output->rotation));
        }
        }
        printf ("\n");






        {
        mode_shown = calloc (output_info->nmode, sizeof (Bool));
        if (!mode_shown) fatal ("out of memory\n");
        for (j = 0; j < output_info->nmode; j++)
        {
            XRRModeInfo *jmode, *kmode;
            int k;

            if (mode_shown[j]) continue;

            jmode = find_mode_by_xid (output_info->modes[j]);
            printf (" ");
            printf ("  %-12s", jmode->name);
            for (k = j; k < output_info->nmode; k++)
            {
            if (mode_shown[k]) continue;
            kmode = find_mode_by_xid (output_info->modes[k]);
            if (strcmp (jmode->name, kmode->name) != 0) continue;
            mode_shown[k] = True;
            kmode->modeFlags |= ModeShown;
            printf (" %6.2f", mode_refresh (kmode));


            mode_i++;
            ScreenMode screeny_mode;
            QString mode_str = jmode->name;
            screeny_mode.height = mode_str.split("x").at(0).toInt();
            screeny_mode.width = mode_str.split("x").at(1).toInt();
            screeny_mode.refreshRate = mode_refresh (kmode);
            screeny_modes.push_back(screeny_mode);

            if (kmode == output->mode_info)
                used_mode = mode_i;

            printf("--%d--", j);

            if (kmode == output->mode_info)
                printf ("*");
            else
                printf (" ");
            }
            printf ("\n");
        }

        MonitorScreen newscreen(screenID, output_info->name, screeny_modes);
        QString connectionstr = connection[output_info->connection];
        newscreen.SetConnected(connectionstr == "connected");
        if (used_mode >= 0)
            newscreen.SetCurrentlyUsedMode(newscreen.GetScreenModes().begin()+used_mode);
        mAvailScreens.push_back(newscreen);

        free (mode_shown);
        }
    }



}

ScreenModeManipulatorLinux::ScreenModeManipulatorLinux()
{
    SearchAvailableScreens();
}

bool ScreenModeManipulatorLinux::SetScreenMode(unsigned int screen, ScreenMode mode)
{

}

