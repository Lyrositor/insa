package fr.insalyon.ihm.util;

import com.google.gson.Gson;
import com.google.gson.JsonObject;


public class JsonConverter {

    private static final Gson gson = new Gson();

    public static String toJson(Object object) {
        return gson.toJson(object);
    }

    public static String toJsonMessage(String field, String content) {
        JsonObject jsonObject = new JsonObject();
        jsonObject.addProperty(field, content);
        return jsonObject.toString();
    }
}
