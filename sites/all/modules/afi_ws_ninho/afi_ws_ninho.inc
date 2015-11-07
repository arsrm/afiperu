<?php
    /**
     * Callback for creating note resources.
     *
     * @param object $data
     * @return object
     */
    function _afi_ws_ninho_create($data) {
      global $user;

      unset($data->id);
      $data->uid = $user->uid;
      $data->created = time();
      $data->modified = time();

      if (!isset($data->subject)) {
        return services_error('Missing note attribute subject', 406);
      }

      if (!isset($data->note)) {
        return services_error('Missing note attribute note', 406);
      }

      noteresource_write_note($data);
      return (object)array(
        'id' => $data->id,
        'uri' => services_resource_uri(array('note', $data->id)),
      );
    }

    /**
     * Callback for updating note resources.
     *
     * @param int $id
     * @param object $data
     * @return object
     */
    function _afi_ws_ninho_update($id, $data) {
      global $user;
      $note = noteresource_get_note($id);

      unset($data->created);
      $data->id = $id;
      $data->uid = $note->uid;
      $data->modified = time();

      noteresource_write_note($data);
      return (object)array(
        'id' => $id,
        'uri' => services_resource_uri(array('note', $id)),
      );
    }

    /**
     * Callback for retrieving note resources.
     *
     * @param int $id
     * @return object
     */
    function _afi_ws_ninho_retrieve($id) {
      $node = node_load($id);
      return $node;
    }

    /**
     * Callback for deleting note resources.
     *
     * @param int $id
     * @return object
     */
    function _afi_ws_ninho_delete($id) {
      noteresource_delete_note($id);
      return (object)array(
        'id' => $id,
      );
    }

    /**
     * Callback for listing notes.
     *
     * @param int $page
     * @param array $parameters
     * @return array
     */
    function _afi_ws_ninho_index($page, $parameters) {
      print_r("123");
      /*
      global $user;

      $notes = array();
      $res = db_query("SELECT * FROM {note} WHERE uid=:uid ORDER BY modified DESC", array(
        ':uid' => $user->uid,
      ));

      while ($note = db_fetch_object($res)) {
        $notes[] = $note;
      }
      */
      $query = db_select('node', 'n');
      $query->condition('n.type', 'ninho', '=');
      $query->orderBy('n.create', 'DESC');
      $items = $query->execute()->fetchAll();
      return $items;
    }
?>