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
    function($scope, $http, $window) {
        $scope.redirect = function(url) {
            $window.location.href = url;
        };

        $scope.utilisateur = null;

        $scope.requete = {order: 'date'};

        $scope.evenements = [];
        sendRequest(
                $http, 'listerEvenementsSansLieu', null,
                function(data) {
                    for (var i in data) {
                        var e = data[i];
                        $scope.evenements.push({
                            activite: e.activite.denomination,
                            date: e.date,
                            id: e.id,
                            participants: e.activite.nbParticipants
                        });
                    }
                }
        );
}]);

CollectIFAdminApp.controller('AdminAssignerCtrl', [
    '$scope', '$http', '$window', '$location',
    function($scope, $http, $window, $location) {
        $scope.redirect = function(url) {
            $window.location.href = url;
        };

        $scope.assignerLieu = function() {
            sendRequest(
                    $http, 'affecterLieu',
                    {
                        evenement: $scope.evenement.id,
                        lieu: $scope.lieuChoisi
                    }
            );
            $scope.redirect('index.html');
        };

        $scope.changerCouleur = function() {
            // Non-fonctionnel
        };

        $scope.evenement = null;
        $scope.lieuChoisi = null;
        $scope.lieux = {};
        $scope.markers = [];
        $scope.map = {center: [0, 0]};

        var params = getSearchParameters();
        var evenementId = parseInt(params.id);
        sendRequest(
                $http, 'getEvenement', { id: evenementId },
                function(data) {
                    if (data === null) {
                        $scope.redirect('index.html');
                        return;
                    }

                    $scope.evenement = {
                        activite: data.activite.denomination,
                        coordonnees: [data.longitude, data.latitude],
                        date: data.date,
                        id: data.id
                    };
                    for (var i in data.participants) {
                        var p = data.participants[i];
                        $scope.markers.push({
                            id: -i,
                            coordonnees: [p.longitude, p.latitude],
                            icone: PIN_URL + '0000FF'
                        });
                    }
                },
                function(data) { $scope.redirect('index.html'); }
        );
        sendRequest(
                $http, 'listerLieux', null,
                function(data) {
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
                    $scope.map = {
                        center: $scope.markers[0].coordonnees,
                        zoom: 11
                    };
                },
                function(data) { $scope.redirect('index.html'); }
        );
}]);