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

        $scope.requete = {order: 'date'};

        $scope.evenements = [];
        sendRequest(
                $http, 'listerEvenementsSansLieu', null,
                function (data) {
                    console.log(data);
                    for (var e in data) {
                        $scope.evenements.push({
                            activite: "Curling sur gazon",
                            date: new Date(),
                            id: 1234,
                            participants: 1254382
                        })
                    }
                }
        );
}]);

CollectIFAdminApp.controller('AdminAssignerCtrl', [
    '$scope', '$http', '$window', '$location',
    function ($scope, $http, $window, $location) {
        $scope.redirect = function(url) {
            $window.location.href = url;
        }

        $scope.assignerLieu = function() {
            sendRequest(
                    $http, 'affecterLieu',
                    {
                        evenementId: $scope.evenement.id,
                        lieuId: $scope.lieux[$scope.lieuChoisi].id
                    }
            );
            $scope.redirect('index.html');
        }

        $scope.changerCouleur = function() {
            // Non-fonctionnel
        }

        $scope.evenement = null;
        $scope.lieuChoisi = null;
        $scope.lieux = {};
        $scope.markers = [];
        $scope.map = {center: [0, 0]};

        var params = getSearchParameters();
        var evenementId = parseInt(params.id);
        sendRequest(
                $http, 'getEvenement', {id: evenementId}, function(data) {
                    $scope.evenement = {
                        activite: data.denomination,
                        coordonnees: [data.longitude, data.latitude],
                        date: data.date,
                        id: data.id
                    };
                    $scope.markers.push({
                            id: -1,
                            coordonnees: $scope.evenement.coordonnees,
                            icone: PIN_URL + '0000FF'
                        });
                    $scope.map = {
                        center: $scope.evenement.coordonnees,
                        zoom: 11
                    };
                }
        );
        sendRequest(
                    $http, 'listerLieux', null,
                    function (data) {
                        $scope.lieux = {};
                        for (var i in data) {
                            var l = data[i];
                            $scope.lieux[l.id] = l.denomination;
                            $scope.markers.push({
                                id: l.id,
                                coordonnees: [l.longitude, l.latitude],
                                icone: PIN_URL + 'FF0000'
                            });
                        }
                    }
        );
}]);