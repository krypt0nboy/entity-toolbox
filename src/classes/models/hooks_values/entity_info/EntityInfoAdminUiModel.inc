<?php

/**
 * Class EntityInfoAdminUiModel
 */
class EntityInfoAdminUiModel extends EntityInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'path'             => array(
            'type'    => 'string',
            'default' => '%toolbox_info_root_path%',
          ),
          'file'             => array(
            'type'   => 'string',
            'default' => '%toolbox_info_classes_ui_controller_file%',
          ),
          'controller class' => array(
            'type'    => 'string',
            'default' => '%toolbox_info_classes_ui_controller_class%',
          ),
          'menu wildcard'    => array(
            'type'    => 'string',
            'default' => '%%toolbox_info_entity_type%',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}