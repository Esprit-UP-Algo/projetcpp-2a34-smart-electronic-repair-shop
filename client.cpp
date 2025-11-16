#include "client.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QSqlError>
#include <QDebug>

Client::Client() {}

Client::Client(int cin, QString nom, QString prenom, QString telephone,
               QString email, QString adresse, QDate dateNaissance)
{
    this->cin = cin;
    this->nom = nom;
    this->prenom = prenom;
    this->telephone = telephone;
    this->email = email;
    this->adresse = adresse;
    this->dateNaissance = dateNaissance;
}

bool Client::validerCin(int cin)
{
    return (cin > 0 && cin <= 99999999);
}

bool Client::validerTelephone(QString telephone)
{
    QRegularExpression regex("^[0-9]{8}$");
    return regex.match(telephone).hasMatch();
}

bool Client::validerEmail(QString email)
{
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return regex.match(email).hasMatch();
}

bool Client::validerNomPrenom(QString texte)
{
    QRegularExpression regex("^[a-zA-ZÀ-ÿ\\s'-]{2,50}$");
    return regex.match(texte).hasMatch();
}

bool Client::existeDeja(int cin)
{
    if (!validerCin(cin)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("SELECT CIN_CLIENT FROM CLIENT WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);

    if(query.exec() && query.next()) {
        return true;
    }
    return false;
}

bool Client::ajouter()
{
    // Validation des données
    if (!validerCin(cin)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le CIN doit être un nombre entre 1 et 99,999,999!");
        return false;
    }

    if (!validerNomPrenom(nom)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le nom n'est pas valide!");
        return false;
    }

    if (!validerNomPrenom(prenom)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le prénom n'est pas valide!");
        return false;
    }

    if (!telephone.isEmpty() && !validerTelephone(telephone)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le téléphone doit contenir 8 chiffres!");
        return false;
    }

    if (!email.isEmpty() && !validerEmail(email)) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "L'email n'est pas valide!");
        return false;
    }

    // Vérifier si le CIN existe déjà
    if(existeDeja(cin)) {
        QMessageBox::warning(nullptr, "Attention", "Ce CIN existe déjà dans la base de données!");
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (CIN_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, DATEN) "
                  "VALUES (:cin, :nom, :prenom, :telephone, :email, :adresse, :dateNaissance)");

    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":adresse", adresse);
    query.bindValue(":dateNaissance", dateNaissance);

    return query.exec();
}

QSqlQueryModel* Client::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT CIN_CLIENT, NOM, PRENOM, TELEPHONE, EMAIL, ADRESSE, DATEN FROM CLIENT");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Naissance"));

    return model;
}

bool Client::supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);

    return query.exec();
}

bool Client::modifier(int cin)
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET NOM = :nom, PRENOM = :prenom, TELEPHONE = :telephone, "
                  "EMAIL = :email, ADRESSE = :adresse, DATEN = :dateNaissance "
                  "WHERE CIN_CLIENT = :cin");

    query.bindValue(":cin", cin);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":adresse", adresse);
    query.bindValue(":dateNaissance", dateNaissance);

    return query.exec();
}

QSqlQueryModel* Client::rechercher(QString critere, QString valeur)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QString requete = "SELECT * FROM CLIENT WHERE ";

    if(critere == "Nom") {
        requete += "NOM LIKE :valeur";
    } else if(critere == "Email") {
        requete += "EMAIL LIKE :valeur";
    } else if(critere == "Téléphone") {
        requete += "TELEPHONE LIKE :valeur";
    }

    QSqlQuery query;
    query.prepare(requete);
    query.bindValue(":valeur", "%" + valeur + "%");
    query.exec();

    model->setQuery(query);
    return model;
}

// ============ IMPLÉMENTATION DES MÉTIERS INNOVANTS ============

int Client::getNombreVisites() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM REPARATION WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

double Client::getTotalDepenses() {
    QSqlQuery query;
    query.prepare("SELECT SUM(COUT) FROM REPARATION WHERE CIN_CLIENT = :cin AND STATUT = 'Terminé'");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

QDate Client::getDerniereVisite() {
    QSqlQuery query;
    query.prepare("SELECT MAX(DATE_DEBUT) FROM REPARATION WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        return query.value(0).toDate();
    }
    return QDate();
}

double Client::getTauxAnnulation() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM REPARATION WHERE CIN_CLIENT = :cin AND STATUT = 'Annulé'");
    query.bindValue(":cin", cin);
    int annulations = 0;
    if (query.exec() && query.next()) {
        annulations = query.value(0).toInt();
    }

    int total = getNombreVisites();
    if (total == 0) return 0.0;

    return (annulations * 100.0) / total;
}

int Client::getVarieteAppareils() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(DISTINCT NUM_SERIE) FROM REPARATION WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    }
    return 0;
}

double Client::getRegulariteVisites() {
    QSqlQuery query;
    query.prepare("SELECT DATEDIFF(MAX(DATE_DEBUT), MIN(DATE_DEBUT)) / COUNT(*) FROM REPARATION WHERE CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);
    if (query.exec() && query.next()) {
        return query.value(0).toDouble();
    }
    return 0.0;
}

double Client::calculerScoreFidelite() {
    int freq = getNombreVisites();
    double depenses = getTotalDepenses();
    double regularite = getRegulariteVisites();
    double tauxAnnulation = getTauxAnnulation();

    // Normalisation des valeurs
    double freqNorm = qMin(freq / 10.0, 1.0) * 100;
    double depensesNorm = qMin(depenses / 1000.0, 1.0) * 100;
    double regulariteNorm = qMin(regularite / 30.0, 1.0) * 100;
    double tauxAnnulationNorm = 100 - tauxAnnulation;

    // Calcul du score selon l'algorithme
    double score = (freqNorm * 0.35) + (depensesNorm * 0.30) +
                   (regulariteNorm * 0.25) + (tauxAnnulationNorm * 0.10);

    return qBound(0.0, score, 100.0);
}

QString Client::getProfilClient() {
    double score = calculerScoreFidelite();

    if (score >= 80) return "Client Fidèle";
    else if (score >= 50) return "Client Standard";
    else return "Client à Risque";
}

int Client::predireProchainRetour() {
    QSqlQuery query;
    query.prepare("SELECT AVG(DATEDIFF(DATE_DEBUT, (SELECT MAX(DATE_DEBUT) FROM REPARATION r2 WHERE r2.CIN_CLIENT = r1.CIN_CLIENT AND r2.DATE_DEBUT < r1.DATE_DEBUT))) "
                  "FROM REPARATION r1 WHERE CIN_CLIENT = :cin AND (SELECT COUNT(*) FROM REPARATION r2 WHERE r2.CIN_CLIENT = r1.CIN_CLIENT AND r2.DATE_DEBUT < r1.DATE_DEBUT) > 0");
    query.bindValue(":cin", cin);

    if (query.exec() && query.next()) {
        int delai = query.value(0).toInt();
        return delai > 0 ? delai : 30;
    }
    return 30;
}

QMap<QString, QVariant> Client::analyserAppareilsMaintenance() {
    QMap<QString, QVariant> resultat;
    QList<QVariant> recommandations;

    QSqlQuery query;
    query.prepare("SELECT DISTINCT a.NUM_SERIE, a.TYPE, a.MARQUE, a.MODELE, a.DATE_ACHAT "
                  "FROM APPAREIL a JOIN REPARATION r ON a.NUM_SERIE = r.NUM_SERIE "
                  "WHERE r.CIN_CLIENT = :cin");
    query.bindValue(":cin", cin);

    if (query.exec()) {
        while (query.next()) {
            QString type = query.value(1).toString();
            QDate dateAchat = query.value(4).toDate();
            int ageMois = dateAchat.daysTo(QDate::currentDate()) / 30;

            QMap<QString, QVariant> reco;
            reco["appareil"] = query.value(2).toString() + " " + query.value(3).toString();
            reco["type"] = type;
            reco["age_mois"] = ageMois;
            reco["numero_serie"] = query.value(0).toString();

            // Règles de maintenance selon le type d'appareil
            if (type.toLower().contains("smartphone") || type.toLower().contains("mobile")) {
                if (ageMois >= 24) {
                    reco["action"] = "Remplacement batterie";
                    reco["priorite"] = "Haute";
                    reco["cout_estime"] = 50.0;
                    reco["description"] = "Batterie usée après 2 ans d'utilisation";
                } else if (ageMois >= 12) {
                    reco["action"] = "Nettoyage port USB";
                    reco["priorite"] = "Moyenne";
                    reco["cout_estime"] = 20.0;
                    reco["description"] = "Maintenance préventive port de charge";
                }
            } else if (type.toLower().contains("ordinateur") || type.toLower().contains("pc") || type.toLower().contains("laptop")) {
                if (ageMois >= 18) {
                    reco["action"] = "Changement pâte thermique";
                    reco["priorite"] = "Haute";
                    reco["cout_estime"] = 40.0;
                    reco["description"] = "Pâte thermique desséchée après 18 mois";
                } else if (ageMois >= 6) {
                    reco["action"] = "Nettoyage ventilateurs";
                    reco["priorite"] = "Moyenne";
                    reco["cout_estime"] = 30.0;
                    reco["description"] = "Nettoyage périodique des systèmes de refroidissement";
                }
            } else if (type.toLower().contains("console")) {
                if (ageMois >= 12) {
                    reco["action"] = "Nettoyage + pâte thermique";
                    reco["priorite"] = "Moyenne";
                    reco["cout_estime"] = 60.0;
                    reco["description"] = "Maintenance annuelle complète";
                }
            }

            if (reco.contains("action")) {
                recommandations.append(reco);
            }
        }
    }

    resultat["recommandations"] = recommandations;
    resultat["nombre_recommandations"] = recommandations.size();
    resultat["client_cin"] = cin;
    resultat["client_nom"] = nom + " " + prenom;
    resultat["date_analyse"] = QDate::currentDate().toString("dd/MM/yyyy");

    return resultat;
}

QMap<QString, QVariant> Client::getDonneesFidelite() {
    QMap<QString, QVariant> donnees;

    donnees["score"] = calculerScoreFidelite();
    donnees["profil"] = getProfilClient();
    donnees["prochain_retour"] = predireProchainRetour();
    donnees["nombre_visites"] = getNombreVisites();
    donnees["total_depenses"] = getTotalDepenses();
    donnees["taux_annulation"] = getTauxAnnulation();
    donnees["variete_appareils"] = getVarieteAppareils();
    donnees["derniere_visite"] = getDerniereVisite().toString("dd/MM/yyyy");
    donnees["regularite"] = getRegulariteVisites();

    return donnees;
}
