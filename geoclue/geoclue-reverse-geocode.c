/*
 * Geoclue
 * geoclue-reverse-geocode.c - Client API for accessing GcIfaceReverseGeocode
 *
 * Author: Iain Holmes <iain@openedhand.com>
 * Copyright 2007 by Garmin Ltd. or its subsidiaries
 */

/**
 * SECTION:geoclue-reverse-geocode
 * @short_description: Geoclue reverse geocode client API
 *
 * #GeoclueReverseGeocode contains reverse geocoding methods. 
 * It is part of the Geoclue public C client API which uses D-Bus 
 * to communicate with the actual provider.
 * 
 * After a #GeoclueReverseGeocode is created with 
 * geoclue_reverse_geocode_new(), the 
 * geoclue_reverse_geocode_position_to_address() method can be used to 
 * obtain the address of a known position.
 */

#include <geoclue/geoclue-reverse-geocode.h>
#include <geoclue/geoclue-marshal.h>

#include "gc-iface-reverse-geocode-bindings.h"

typedef struct _GeoclueReverseGeocodePrivate {
	int dummy;
} GeoclueReverseGeocodePrivate;

#define GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), GEOCLUE_TYPE_REVERSE_GEOCODE, GeoclueReverseGeocodePrivate))

G_DEFINE_TYPE (GeoclueReverseGeocode, geoclue_reverse_geocode, GEOCLUE_TYPE_PROVIDER);

static void
finalize (GObject *object)
{
	G_OBJECT_CLASS (geoclue_reverse_geocode_parent_class)->finalize (object);
}

static void
dispose (GObject *object)
{
	G_OBJECT_CLASS (geoclue_reverse_geocode_parent_class)->dispose (object);
}

static void
geoclue_reverse_geocode_class_init (GeoclueReverseGeocodeClass *klass)
{
	GObjectClass *o_class = (GObjectClass *) klass;

	o_class->finalize = finalize;
	o_class->dispose = dispose;

	g_type_class_add_private (klass, sizeof (GeoclueReverseGeocodePrivate));
}

static void
geoclue_reverse_geocode_init (GeoclueReverseGeocode *geocode)
{
}

/**
 * geoclue_reverse_geocode_new:
 * @service: D-Bus service name
 * @path: D-Bus path name
 *
 * Creates a #GeoclueReverseGeocode with given D-Bus service name and path.
 * 
 * Return value: Pointer to a new #GeoclueReverseGeocode
 */
GeoclueReverseGeocode *
geoclue_reverse_geocode_new (const char *service,
			     const char *path)
{
	return g_object_new (GEOCLUE_TYPE_REVERSE_GEOCODE,
			     "service", service,
			     "path", path,
			     "interface", GEOCLUE_REVERSE_GEOCODE_INTERFACE_NAME,
			     NULL);
}

/**
 * geoclue_reverse_geocode_position_to_address:
 * @geocode: A #GeoclueReverseGeocode object
 * @latitude: latitude in degrees
 * @longitude: longitude in degrees
 * @details: Pointer to returned #GHashTable with address details or %NULL
 * @error: Pointer to returned #Gerror or %NULL
 * 
 * Obtains an address for the position defined by @latitude and @longitude.
 * @details is a #GHashTable with the returned address data, see 
 * geoclue-types.h for the hashtable keys.
 * 
 * If the caller is not interested in some values, the pointers can be 
 * left %NULL.
 * 
 * Return value: %TRUE if there is no @error
 */
gboolean
geoclue_reverse_geocode_position_to_address (GeoclueReverseGeocode   *geocode,
					     double                   latitude,
					     double                   longitude,
					     GHashTable             **details,
					     GError                 **error)
{
	GeoclueProvider *provider = GEOCLUE_PROVIDER (geocode);
	
	if (!org_freedesktop_Geoclue_ReverseGeocode_position_to_address 
	    (provider->proxy, latitude, longitude, details, error)) {

		return FALSE;
	}

	return TRUE;
}
