<?php

/**
 * Class EntityToolboxUIControllerNotFieldable
 *
 * The default UI Controller for non fieldable entities.
 */
class EntityToolboxUIControllerNotFieldable extends EntityToolboxUIController {

  /**
   * Provides the menu items for hook_menu().
   *
   * @see hook_menu().
   */
  public function hook_menu() {
    $items                                                    = array();
    $id_count                                                 = $this->id_count;
    $label                                                    = $this->labelSingle();
    $label_plural                                             = $this->labelPlural();
    $create_callback                                          = $this->toolboxInfo['callbacks']['create'];
    $access_callback                                          = $this->toolboxInfo['callbacks']['access'];
    $page_callback                                            = $this->toolboxInfo['callbacks']['page'];
    $title_callback                                           = $this->toolboxInfo['callbacks']['title'];
    $wildcard                                                 = $this->wildcard();
    $items[$this->path]                                       = array(
      'title'            => $label_plural,
      'page callback'    => 'drupal_get_form',
      'page arguments'   => array(
        $this->entityType . '_overview_form',
        $this->entityType
      ),
      'description'      => 'Manage ' . $label_plural . ', including adding
		and removing fields and the display of fields.',
      'access callback'  => 'entity_access',
      'access arguments' => array('view', $this->entityType),
      'file'             => 'includes/entity.ui.inc',
    );
    $items[$this->path . '/add']                              = array(
      'title'            => "Add a $label",
      'page callback'    => 'entity_toolbox_ui_edit_form',
      'page arguments'   => array(entity_create($this->entityType, array())),
      'access callback'  => $access_callback,
      'access arguments' => array('create', $this->entityType),
      'type'             => MENU_LOCAL_ACTION,
      'weight'           => 20,
      'file'             => 'entity_toolbox.entities.functions.inc',
      'file path'        => ENTITY_TOOLBOX_PATH,
    );
    $items[$this->path . '/manage/%entity_object']            = array(
      'title'            => 'Edit',
      'title callback'   => 'entity_label',
      'title arguments'  => array($this->entityType, $id_count + 1),
      'page callback'    => 'entity_toolbox_ui_edit_form',
      'page arguments'   => array($id_count + 1, $this->entityType),
      'load arguments'   => array($this->entityType),
      'access callback'  => $access_callback,
      'access arguments' => array('update', $this->entityType, $id_count + 1),
      'file'             => 'entity_toolbox.entities.functions.inc',
      'file path'        => ENTITY_TOOLBOX_PATH,
    );
    $items[$this->path . '/manage/%entity_object/edit']       = array(
      'title'          => 'Edit',
      'load arguments' => array($this->entityType),
      'type'           => MENU_DEFAULT_LOCAL_TASK,
    );
    $items[$this->path . '/manage/%entity_object' . '/clone'] = array(
      'title'            => 'Clone',
      'page callback'    => 'entity_toolbox_ui_clone_form',
      'page arguments'   => array($id_count + 1, $this->entityType),
      'load arguments'   => array($this->entityType),
      'access callback'  => $access_callback,
      'access arguments' => array('create', $this->entityType),
    );
    $items[$this->path . '/manage/%entity_object' . '/%']     = array(
      'page callback'    => 'drupal_get_form',
      'page arguments'   => array(
        $this->entityType . '_operation_form',
        $this->entityType,
        $id_count + 1,
        $id_count + 2
      ),
      'load arguments'   => array($this->entityType),
      'access callback'  => $access_callback,
      'access arguments' => array('delete', $this->entityType, $id_count + 1),
      'file'             => 'includes/entity.ui.inc',
    );

    if (!empty($this->entityInfo['exportable']) && $this->entityInfo) {
      $items[$this->path . '/import'] = array(
        'title callback'   => 'entity_ui_get_action_title',
        'title arguments'  => array('import', $this->entityType),
        'page callback'    => 'drupal_get_form',
        'page arguments'   => array(
          $this->entityType . '_operation_form',
          $this->entityType,
          NULL,
          'import'
        ),
        'access callback'  => $access_callback,
        'access arguments' => array('create', $this->entityType),
        'file'             => 'includes/entity.ui.inc',
        'type'             => MENU_LOCAL_ACTION,
      );
    }

  }
}