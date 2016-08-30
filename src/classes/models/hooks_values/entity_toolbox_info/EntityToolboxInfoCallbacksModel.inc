<?php

/**
 * Class EntityToolboxInfoCallbacksModel
 */
class EntityToolboxInfoCallbacksModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'  => 'callbacks',
        'structure' => array(
          'create' => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%_create',
          ),
          'save'   => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%_save',
          ),
          'delete' => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%_delete',
          ),
          'access' => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%_access',
          ),
          'label'  => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%_label',
          ),
          'uri'    => array(
            'type'    => 'string',
            'default' => '%toolbox_info_entity_type%_uri',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}