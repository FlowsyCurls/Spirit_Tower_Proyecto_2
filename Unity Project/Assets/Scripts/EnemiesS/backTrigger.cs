using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class backTrigger : MonoBehaviour
{

    public GameObject targetEnemy;
    public GameObject player;
    private IDictionary<string, int> pointsDictionary = new Dictionary<string, int>()
    {
        {"spectre_gray", 10},
        {"spectre_blue", 20},
        {"spectre_red", 25},
        {"chuchu", 15},
        {"spectralEye", 10},
        {"mouse", 5},
        {"jarron", 30 }
    };

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider collider)
    {
        if (collider.gameObject.tag == "Sword" && collider.GetComponent<AttackS>().isAttacking) {
            Debug.Log("Ataca jugador por espalda a : " + targetEnemy.GetComponent<EnemyScript>().id);
            player.GetComponent<PlayerMovement>().score += pointsDictionary[targetEnemy.GetComponent<EnemyScript>().id];
            Destroy(targetEnemy);
        }
    }

}
