TD Web sémantique 4-IF-WS (2016–2017)
=====================================

1 Découverte
------------

2 SPARQL
--------

2.3 Trouver la requête

```sparql
PREFIX insa: <http://insa-lyon.fr/insa#>
PREFIX ue: <http://insa-lyon.fr/ue#>
PREFIX foaf: <http://xmlns.com/foaf/spec/>
SELECT ?e2 ?n2 WHERE
{
?e insa:binome ?e2; foaf:name ?n .
?e2 foaf:name ?n2 .
FILTER(?n = "Alice")
}
```

3 DBPedia
---------

1. 

```sparql
PREFIX dbo: <http://dbpedia.org/ontology/>

SELECT ?country WHERE {
?country rdf:type dbo:Country; dbo:populationTotal ?population; rdfs:label ?label .
FILTER (?population > 15000000 && langMatches(lang(?label), "EN"))
}
```

2. 
```sparql
PREFIX dbo: <http://dbpedia.org/ontology/>

SELECT ?country ?label ?est WHERE
{
?country rdf:type dbo:Country; dbpedia2:establishedDate ?est; rdfs:label ?label .
FILTER (langMatches(lang(?label), "EN") && bif:contains(?label, "Republic") && ?est < "1920-01-01"^^xsd:date)
}
```

3.
```sparql
PREFIX dbo: <http://dbpedia.org/ontology/>

SELECT ?country WHERE {
?country rdf:type dbo:Country ; dbo:populationTotal ?population.
?country dbo:currency dbr:Euro.
?country dbo:language dbr:French_language.
FILTER (?population < 15000)
}
```

4. *Not available.*
