<?php

/**
 * Class EntityInfoAdminUiModel
 */
class EntityInfoOperationsUiModel extends EntityInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'controller class' => array(
            'type'    => 'string',
            'default' => 'EntityOperationsDefaultUIController',
          ),
          'path'             => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%',
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