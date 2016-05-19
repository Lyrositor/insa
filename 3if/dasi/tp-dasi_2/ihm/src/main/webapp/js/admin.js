var CollectIFAdminApp = angular.module(
    'CollectIFAdminApp',
    ['ngMaterial', 'md.data.table', 'uiGmapgoogle-maps']
).config([
    'uiGmapGoogleMapApiProvider',
    function(uiGmapGoogleMapApiProvider) {
        uiGmapGoogleMapApiProvider.configure({
            key: CLE_API,
            libraries: 'geometry,visualization'
        });
    }
]);

CollectIFAdminApp.controller('AdminHomeCtrl', ['$scope', '$http', '$window',
    function ($scope, $http, $window) {
        $scope.redirect = function(url) {
            $window.location.href = url;
        }

        $scope.utilisateur = null;

        $scope.requete = {
            order: 'date'
        };

        $scope.evenements = [
            {
                activite: "Curling sur gazon",
                date: new Date(),
                id: 1234,
                participants: 1254382
            },
            {
                activite: "Hockey",
                date: new Date(2013, 2, 2),
                id: 1235,
                participants: 3
            }
        ];
}]);

CollectIFAdminApp.controller('AdminAssignerCtrl', ['$scope', '$http', '$window',
    function ($scope, $http, $window) {
        $scope.redirect = function(url) {
            $window.location.href = url;
        }

        $scope.assignerLieu = function() {
            alert('test');
        }
        $scope.changerCouleur = function() {
            $scope.markers[$scope.lieuChoisi].icone = PIN_URL + '00FF00';
            $scope.map.control.refresh();
        }

        $scope.demande = {
            activite: "Tarot",
            coordonnees: [12, 9],
            date: new Date()
        };
        $scope.lieuChoisi = null;
        $scope.lieux = [
            {id: 0, nom: "Piscine de Truc", coordonnees: [10, 10], icone: PIN_URL + 'FF0000'},
            {id: 1, nom: "Gymnase de Chose", coordonnees: [9, 13], icone: PIN_URL + 'FF0000'}
        ];
        $scope.markers = $scope.lieux;
        $scope.markers.push({id: -1, coordonnees: $scope.demande.coordonnees, icone: PIN_URL + '0000FF'})
        $scope.map = { center: $scope.demande.coordonnees, zoom: 8 };
}]);