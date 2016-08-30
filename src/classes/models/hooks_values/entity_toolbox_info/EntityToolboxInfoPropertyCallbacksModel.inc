<?php

/**
 * Class EntityToolboxInfoPropertyCallbacksModel
 */
class EntityToolboxInfoPropertyCallbacksModel extends EntityToolboxInfoRecursiveModel {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'self_key'  => 'callbacks',
        'structure' => array(
          'getter'       => array(
            'type'    => 'string',
            'method'  => 'buildGetterCallback',
            'default' => '%property_default_callbacks_getter%',
          ),
          'setter'       => array(
            'type'    => 'string',
            'method'  => 'buildSetterCallback',
            'default' => '%property_default_callbacks_setter%',
          ),
          'validation'   => array(
            'type'    => 'string',
//            'method'  => 'buildValidationCallback',
            'default' => '%property_default_callbacks_validation%',
          ),
          'permission'   => array(
            'type'    => 'string',
//            'method'  => 'buildPermissionCallback',
            'default' => '%property_default_callbacks_permission%',
          ),
          'default'      => array(
            'type'    => 'string',
//            'method'  => 'buildDefaultValueCallback',
            'default' => '%property_default_callbacks_default_value%',
          ),
          'options list' => array(
            'type'    => 'string',
//            'method'  => 'buildOptionsListCallback',
            'default' => '%property_default_callbacks_options_list%',
          ),
        )
      ),
      $args
    );
    parent::__construct($args);
  }
}