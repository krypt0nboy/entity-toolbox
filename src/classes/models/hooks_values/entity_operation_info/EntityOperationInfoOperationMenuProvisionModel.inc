<?php

/**
 * Class EntityOperationsInfoOperationMenuProvisionModel
 */
class EntityOperationInfoOperationMenuProvisionModel extends EntityOperationInfoOperationProvisionModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'structure' => array(
          'default'   => array(
            'type'    => 'boolean',
            'default' => '',
          ),
          'menu item' => array(
            'type'    => 'array',
            'model'   => 'menu_item_model',
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}


