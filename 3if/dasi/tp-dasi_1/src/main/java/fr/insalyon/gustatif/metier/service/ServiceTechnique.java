package fr.insalyon.gustatif.metier.service;

import com.google.maps.DirectionsApi;
import com.google.maps.DirectionsApiRequest;
import com.google.maps.GeoApiContext;
import com.google.maps.GeocodingApi;
import com.google.maps.model.DirectionsResult;
import com.google.maps.model.DirectionsRoute;
import com.google.maps.model.GeocodingResult;
import com.google.maps.model.LatLng;
import com.google.maps.model.TravelMode;

public class ServiceTechnique {

    final static String CLE_GOOGLE_API = "AIzaSyDcVVJjfmxsNdbdUYeg9MjQoJJ6THPuap4";
    final static GeoApiContext CONTEXTE_GEOAPI = new GeoApiContext().setApiKey(CLE_GOOGLE_API);

    public static void envoyerMail(String expediteur, String destinataire, String objet, String corps) {
        System.out.println(" --- Mail --- ");
        System.out.println("Expediteur : " + expediteur);
        System.out.println("Destinataire : " + destinataire);
        System.out.println("Objet : " + objet);
        System.out.println("Corps :\n" + corps);
        System.out.println(" --- ---- --- ");
    }

    public static LatLng getLatLng(String adresse) {
        try {
            GeocodingResult[] results = GeocodingApi.geocode(CONTEXTE_GEOAPI, adresse).await();

            return results[0].geometry.location;

        } catch (Exception ex) {
            return null;
        }
    }

    public static double toRad(double angleInDegree) {
        return angleInDegree * Math.PI / 180.0;
    }

    public static double getFlightDistanceInKm(LatLng origin, LatLng destination) {

        // From: http://www.movable-type.co.uk/scripts/latlong.html
        double R = 6371.0; // Average radius of Earth (km)
        double dLat = toRad(destination.lat - origin.lat);
        double dLon = toRad(destination.lng - origin.lng);
        double lat1 = toRad(origin.lat);
        double lat2 = toRad(destination.lat);

        double a = Math.sin(dLat / 2.0) * Math.sin(dLat / 2.0)
                + Math.sin(dLon / 2.0) * Math.sin(dLon / 2.0) * Math.cos(lat1) * Math.cos(lat2);
        double c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1.0 - a));
        double d = R * c;

        return d;
    }

    public static Double getTripDurationByBicycleInMinute(LatLng origin, LatLng destination, LatLng... steps) {
        return getTripDurationOrDistance(TravelMode.BICYCLING, true, origin, destination, steps);
    }

    public static Double getTripDistanceByCarInKm(LatLng origin, LatLng destination, LatLng... steps) {
        return getTripDurationOrDistance(TravelMode.DRIVING, false, origin, destination, steps);
    }

    public static Double getTripDurationOrDistance(TravelMode mode, boolean duration, LatLng origin, LatLng destination, LatLng... steps) {

        DirectionsApiRequest request = DirectionsApi.getDirections(CONTEXTE_GEOAPI, origin.toString(), destination.toString());
        request.mode(mode);
        request.region("fr");

        if (steps.length > 0) {

            String[] stringSteps = new String[steps.length];
            for (int i = 0; i < steps.length; i++) {
                stringSteps[i] = steps[i].toString();
            }

            request.waypoints(stringSteps);
        }

        double cumulDistance = 0.0;
        double cumulDuration = 0.0;

        try {
            DirectionsResult result = request.await();
            DirectionsRoute[] directions = result.routes;

            for (int legIndex = 0; legIndex < directions[0].legs.length; legIndex++) {

                cumulDistance += directions[0].legs[legIndex].distance.inMeters / 1000.0;
                cumulDuration += Math.ceil(directions[0].legs[legIndex].duration.inSeconds / 60.0);
            }

        } catch (Exception ex) {
            return null;
        }

        if (duration) {
            return cumulDuration;
        } else {
            return cumulDistance;
        }
    }
}
