using System.Data;
using UnityEngine;

public class PlayerMovement : MonoBehaviour
{

    public float speed;
    private string dir;
    private string lastDir;
    public static int row;
    public static int column;
    public int lostLifes;
    public int score;

    public bool isBlocking;
    public bool hasFall;

    // Start is called before the first frame update
    void Start()
    {
        row = 0;
        column = 0;
        lostLifes = 0;
        score = 0;
        dir = "none";
        lastDir = "none";
        hasFall = false;
        isBlocking = false;
    }

    // Update is called once per frame
    void Update()
    {
        //Checks if the speed limit is reached

        if (Input.GetKey(KeyCode.LeftShift))
        {
            speed = 10f;
        }
        else
        {
            speed = 4f;
        }

        //If the player fall because a trap, the z axis value is negative, this indicates that the player is dead
        if (this.transform.position.y < -5) {
            Debug.Log(" Caí en la trampa !!! ");
            hasFall = true;
        }

        if (Input.GetKey(KeyCode.Q)) {
            Debug.Log(" Bloqueando");
            isBlocking = true;
        }
        if (Input.GetKeyUp(KeyCode.Q)) {
            Debug.Log("No Bloqueando");
            isBlocking = false;
        }

        if (Input.GetKey(KeyCode.UpArrow))
            {
                //Move the Rigidbody forwards constantly at speed you define (the blue arrow axis in Scene view)
                setLastDir(dir);
                setDir("up");
            
                transform.Translate(transform.forward * speed * Time.deltaTime);

            }

            if (Input.GetKey(KeyCode.DownArrow))
            {
                //Move the Rigidbody backwards constantly at the speed you define (the blue arrow axis in Scene view)
                setLastDir(dir);
                setDir("down");
                transform.Translate(-transform.forward * speed * Time.deltaTime);
                
            }

            if (Input.GetKey(KeyCode.RightArrow))
            {
                setLastDir(dir);
                setDir("right");
                transform.Translate(transform.right * speed * Time.deltaTime);
            }

            if (Input.GetKey(KeyCode.LeftArrow))
            {
                setLastDir(dir);
                setDir("left");
                transform.Translate(-transform.right * speed * Time.deltaTime);
            }
            
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.collider.tag == "Enemy" && this.isBlocking == false) {
            
            if (this.lostLifes >= 5) {
                Debug.Log("Perdí");
                Program.sendMessage("Pierde el jugador");
            }

            this.lostLifes++;
            Debug.Log("Me pegó un enemigo, pierdo vidas :(!!!");
            Debug.Log("Perdí: " + this.lostLifes + " vidas");
            Program.sendMessage("Pierdo vida, me quitaron " + this.lostLifes + " vidas");
        }
        
    }

    private void setDir(string _dir) {
        dir = _dir;
    }

    public string getDir() {
        return dir;
    }

    private void setLastDir(string _dir)
    {
        lastDir = _dir;
    }

    public string getLastDir()
    {
        return lastDir;
    }


}